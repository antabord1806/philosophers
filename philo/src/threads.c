#include "../include/structs.h"
#include "../include/philo.h"

long long   current_miliseconsds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void     starving_city(thread_info_t *ti, long long start, long long end, long long time_to_die)
{
    if (time_to_die <= (end - start))
    {
        printf("rip\n");
        exit(127);
    }
    else
    {
        ti->time->start_time = 0;
        ti->time->end_time = 0;
        return;
    }
}

/* static void     grabbing_forks(thread_info_t *thread_info, int first, int second)
{
    pthread_mutex_lock
} */

static void    *pantry(void *args)
{
    thread_info_t   *thread_info;
    int first;
    int second;

    thread_info = (thread_info_t *)args;
    first = thread_info->thread_id;
    if (thread_info->thread_id != thread_info->n_forks)
        second = (thread_info->thread_id + 1) % thread_info->n_forks;
    else 
        second = 0;
    while (1)
    {
        pthread_mutex_lock(thread_info->time_mutex);
        thread_info->time->start_time = current_miliseconsds();
        pthread_mutex_unlock(thread_info->time_mutex);
        pthread_mutex_lock(&thread_info->fork[first].m);
        thread_info->time->end_time = current_miliseconsds();
        
        pthread_mutex_lock(thread_info->print_mutex);
        starving_city(thread_info, thread_info->time->start_time, thread_info->time->end_time, thread_info->time->time_to_die);
        printf("mutex: %p bloquado pela thread: %d\n", (void *)&thread_info->fork[first].m, thread_info->thread_id);
        pthread_mutex_unlock(thread_info->print_mutex);

        pthread_mutex_lock(thread_info->time_mutex);
        thread_info->time->start_time = current_miliseconsds();
        pthread_mutex_lock(&thread_info->fork[second].m);
        thread_info->time->end_time = current_miliseconsds();
        starving_city(thread_info, thread_info->time->start_time, thread_info->time->end_time, thread_info->time->time_to_die);
        pthread_mutex_unlock(thread_info->time_mutex);
        
        pthread_mutex_lock(thread_info->print_mutex);
        printf("mutex: %p bloquado pela thread: %d\n", (void *)&thread_info->fork[second].m, thread_info->thread_id);
        pthread_mutex_unlock(thread_info->print_mutex);

        pthread_mutex_lock(thread_info->time_mutex);
        thread_info->time->start_time = current_miliseconsds();
        usleep(thread_info->time->time_to_eat * 1000);
        thread_info->time->end_time = current_miliseconsds();
        starving_city(thread_info, thread_info->time->start_time, thread_info->time->end_time, thread_info->time->time_to_die);
        pthread_mutex_unlock(thread_info->time_mutex);
        
        pthread_mutex_unlock(&thread_info->fork[first].m);
        pthread_mutex_lock(thread_info->print_mutex);
        printf("mutex: %p desbloquado pela thread: %d\n", (void *)&thread_info->fork[first].m, thread_info->thread_id);
        pthread_mutex_unlock(thread_info->print_mutex);
        
        pthread_mutex_unlock(&thread_info->fork[second].m);
        pthread_mutex_lock(thread_info->print_mutex);
        printf("mutex: %p desbloquado pela thread: %d\n", (void *)&thread_info->fork[second].m, thread_info->thread_id);
        pthread_mutex_unlock(thread_info->print_mutex);

        pthread_mutex_lock(thread_info->time_mutex);
        usleep(thread_info->time->sleep_time * 1000);
        pthread_mutex_unlock(thread_info->time_mutex);
    }
    return NULL;
}

int     thread_creator(thread_info_t *ti)
{
    int i;
    
    i = -1;
    while (++i < ti->n_forks)
    {
        pthread_mutex_init(&ti->fork[i].m, NULL);
        printf("mutex criada: %p\n", (void *)&ti->fork[i].m);
    }
    i = -1;
    while (++i < ti->n_forks)
    {
        if (pthread_create(&ti[i].th, NULL, pantry, &ti[i]) != 0)
            printf("ERROR grabbing fork\n");
        printf("thread criada: %d\n", ti[i].thread_id);
        //usleep(1000);
    }
    i = -1;
    while (++i < ti->n_forks)
        pthread_join(ti[i].th, NULL);
    return (0);
}


static long long	ft_atol(char *str)
{
    long long	result;
    long long   total;
	int		sign;
    
	result = 0;
	sign = 1;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)))
        str++;
	if (*str == '-' || *str == '+')
	{
        if (*str == '-')
        sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
        result = result * 10 + (*str - '0');
		str++;
	}
    total = result * sign;
    if (total < 0)
        return (0);
    else
        return (total);
}

static void    thread_info_filler(thread_info_t *ti, helper_struct_t *helper)
{
    int i;

    i = 0;
    while (i < helper->n_forks)
    {

        ti[i].th = 0;
        ti[i].fork = helper->mutex;
        ti[i].print_mutex = &helper->print_mutex;
        ti[i].time_mutex = &helper->time_mutex;
        ti[i].time = helper->time;
        ti[i].fork[i].locked_status = false;
        ti[i].status = WAITING_0;
        ti[i].thread_id = i;
        ti[i].n_forks = helper->n_forks;
        ti[i].life_status = ALIVE;
        i++;
    }
}
int     norminette_won(thread_info_t *ti, helper_struct_t *helper)
{
    if (pthread_mutex_init(&helper->print_mutex, NULL) != 0 || pthread_mutex_init(&helper->time_mutex, NULL) != 0)
    {
        printf("print mutex or getting time mutex init failed\n");
        free(helper->mutex);
        free(ti);
        return (0);
    }
    printf("print mutex criada: %p\n", (void *)&helper->print_mutex);
    printf("time mutex criada: %p\n", (void *)&helper->time_mutex);
    thread_info_filler(ti, helper);
    thread_creator(ti);
    return (0);
}
int     main(int argc, char *argv[])
{
    mutex_tracker_t *mutex;
    thread_info_t   *ti;
    helper_struct_t helper;
    philo_time_t time;
    long long   n_forks;
    
    if (argc != 6)
        return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    ti = malloc(n_forks * sizeof(thread_info_t));
    if (!ti || !mutex)
        return (0);
    time.time_to_die = ft_atol(argv[2]);
    time.time_to_eat = ft_atol(argv[3]);
    time.sleep_time = ft_atol(argv[4]);
    if (argc == 6)
        time.n_times = ft_atol(argv[5]);
    else
        time.n_times = -1;
    helper.mutex = mutex;
    helper.n_forks = n_forks;
    helper.time = &time;
    norminette_won(ti,&helper);
}

