#include "../include/structs.h"
#include "../include/philo.h"

long long   current_miliseconsds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void    *pantry(void *args)
{
    thread_info_t   *thread_info;
    int first;
    int second;

    thread_info = (thread_info_t *)args;
    first = thread_info->thread_id;
    second = (thread_info->thread_id + 1) % thread_info->n_forks;
    thread_info->start_time = current_miliseconsds();
    while (thread_info->life_status == ALIVE)
    {
/*         if (thread_info->fork[first].locked_status == true)
        {
            usleep(thread_info->time_to_die * 1000);
            if (thread_info->fork[first].locked_status == true)
                thread_info->life_status = DEAD;
        } */
        pthread_mutex_lock(&thread_info->fork[first].m);
        thread_info->fork[first].locked_status = true;
        printf("mutex: %p bloquado pela thread: %d\n", (void *)&thread_info->fork[first].m, thread_info->thread_id);
/*         if (thread_info->fork[second].locked_status == true)
        {
            usleep(thread_info->time_to_die * 1000);
            if (thread_info->fork[second].locked_status == true)
                thread_info->life_status = DEAD;
        } */
        pthread_mutex_lock(&thread_info->fork[second].m);
        thread_info->fork[second].locked_status = true;
        printf("mutex: %p bloquado pela thread: %d\n", (void *)&thread_info->fork[second].m, thread_info->thread_id);
        usleep(thread_info->fork[first].time_to_eat * 1000);
        pthread_mutex_unlock(&thread_info->fork[first].m);
        thread_info->fork[first].locked_status = false;
        printf("mutex: %p desbloquado pela thread: %d\n", (void *)&thread_info->fork[first].m, thread_info->thread_id);
        pthread_mutex_unlock(&thread_info->fork[second].m);
        thread_info->fork[second].locked_status = true;
        printf("mutex: %p desbloquado pela thread: %d\n", (void *)&thread_info->fork[second].m, thread_info->thread_id);
    }
    usleep(thread_info->sleep_time * 1000);
    return NULL;
}

static void    starter_args(mutex_tracker_t *mutex, thread_info_t *args, int n_forks, int i)
{
    args[i].th = 0;
    args[i].fork = mutex;
    args[i].fork[i].locked_status = false;
    args[i].status = WAITING_0;
    args[i].thread_id = i;
    args[i].n_forks = n_forks;
    args[i].life_status = ALIVE;
    args[i].fork[i].locked_status = false;
    args[i].fork[i].owner = 0;
    args[i].fork[i].start_time = 0;
}
int     thread_creator(mutex_tracker_t *mutex, int n_forks)
{
    thread_info_t args[n_forks];
    int i;

    i = -1;
    while (++i < n_forks)
    {
        pthread_mutex_init(&mutex[i].m, NULL);
        printf("mutex criada: %p\n", (void *)&mutex[i].m);
        starter_args(mutex, args, n_forks, i);
    }
    i = -1;
    while (++i < n_forks)
    {
        if (pthread_create(&args[i].th, NULL, pantry, &args[i]) != 0)
            printf("ERROR grabbing fork\n");
        printf("thread criada: %d\n", args[i].thread_id);
        usleep(10000);
    }
    i = -1;
    while (++i < n_forks)
        pthread_join(args[i].th, NULL);
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

int     main(int argc, char *argv[])
{
    mutex_tracker_t *mutex;
    thread_info_t   thread_info;
    long long   n_forks;

    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    if (!mutex)
        return (0);
    memset(&thread_info, 0, sizeof(thread_info));
    thread_info.time_to_die = ft_atol(argv[2]);
    mutex->time_to_eat = ft_atol(argv[3]);
    thread_info.sleep_time = ft_atol(argv[4]);
    if (argc == 6)
        thread_info.number_of_times_to_eat = ft_atol(argv[5]);
    else
        thread_info.number_of_times_to_eat = -1;
    thread_creator(mutex, (int)n_forks);
    free(mutex);
}
