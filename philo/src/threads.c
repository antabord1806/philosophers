#include "../include/structs.h"
#include "../include/philo.h"

long long   current_miliseconsds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void     starving_city(philo_info_t *ti, long long start, long long end, long long time_to_die)
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

static void    *pantry(void *args)
{
    philo_info_t   *philo_info;
    int first;
    int second;

    philo_info = (philo_info_t *)args;
    first = philo_info->thread_id;
    if (philo_info->thread_id != philo_info->n_forks)
        second = (philo_info->thread_id + 1) % philo_info->n_forks;
    else 
        second = 0;
    pthread_mutex_lock(ti[i].last_meal_ms)
    while (1)
    {

    }
    return NULL;
}

int     philo_creator(philo_info_t *ti)
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

static void    philo_info_filler(philo_info_t *ti, helper_struct_t *helper)
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
        ti[i].thread_id = i;
        ti[i].n_forks = helper->n_forks;
        ti[i].last_meal_ms = current_miliseconsds();
        i++;
    }
}
int     norminette_won(philo_info_t *ti, helper_struct_t *helper)
{
    if (pthread_mutex_init(&helper->print_mutex, NULL) != 0 || pthread_mutex_init(&helper->time_mutex, NULL) != 0)
        return (printf("print mutex or getting time mutex init failed\n"),free(helper->mutex), free(ti), 0);
    printf("print mutex criada: %p\n", (void *)&helper->print_mutex);
    printf("time mutex criada: %p\n", (void *)&helper->time_mutex);
    philo_info_filler(ti, helper);
    pthread_create(&monitor, NULL, life_check)
    philo_creator(ti);
    return (0);
}
int     main(int argc, char *argv[])
{
    mutex_tracker_t *mutex;
    philo_info_t   *ti;
    helper_struct_t helper;
    philo_time_t time;
    long long   n_forks;
    
    if (argc != 6)
        return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    ti = malloc(n_forks * sizeof(philo_info_t));
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

