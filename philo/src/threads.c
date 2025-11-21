#include "../include/structs.h"
#include "../include/philo.h"

static void     sleeping_time(philo_info_t *pi, long long start, long long first, long long second)
{
    long long   timestamp;

    pthread_mutex_lock(pi->time_mutex);
    timestamp = current_miliseconsds() - start;
    pthread_mutex_unlock(pi->time_mutex);
    pthread_mutex_lock(pi->print_mutex);
    printf("%lld philo %d is sleeping\n", timestamp, pi->thread_id);
    pthread_mutex_unlock(pi->print_mutex);
    usleep(pi->sleep_time * 1000);
}

static void     eating_spaggeti(philo_info_t *pi, long long start, long long first, long long second)
{
    long long timetstamp;

    pthread_mutex_lock(&pi->fork[first]);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds() - start;
    pthread_mutex_unlock(pi->time_mutex);
    pthread_mutex_lock(pi->print_mutex);
    printf("%lld philo %d has taken a fork\n", timetstamp, pi->thread_id);
    pthread_mutex_unlock(pi->print_mutex);
    pthread_mutex_lock(&pi->fork[second]);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds() - start;
    pthread_mutex_unlock(pi->time_mutex);
    pthread_mutex_lock(pi->print_mutex);
    printf("%lld philo %d has taken a fork\n", timetstamp, pi->thread_id);
    pthread_mutex_unlock(pi->print_mutex);
    usleep(pi->time_to_eat * 1000);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds() - start;
    pi->last_meal_ms = timetstamp;
    pthread_mutex_unlock(pi->time_mutex);
    pthread_mutex_lock(pi->print_mutex);
    printf("%lld philo %d is eating\n", timetstamp, pi->thread_id);
    pthread_mutex_unlock(pi->print_mutex);
    return ;
}

static void    pantry(void *args)
{
    philo_info_t   *pi;
    int first;
    long long second;
    long long start;
    long long timetstamp;

    pi = (philo_info_t *)args;
    first = pi->thread_id;
    if (pi->thread_id != pi->n_forks)
        second = (pi->thread_id + 1) % pi->n_forks;
    else 
        second = 0;
    while (1)
    {
        pthread_mutex_lock(pi->time_mutex);
        start = current_miliseconsds();
        pthread_mutex_unlock(pi->time_mutex);
        eating_spaggeti(pi, start, first, second);
        pthread_mutex_lock(pi->time_mutex);
        timetstamp = current_miliseconsds() - start;
        pthread_mutex_unlock(&pi->fork[first]);
        pthread_mutex_unlock(&pi->fork[second]);
        pthread_mutex_unlock(pi->time_mutex);
        sleeping_time(pi, start, first, second);
    }
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

void    struct_filler(philo_info_t *ti, fork_tracker_t *mutex, char *argv[])
{
    philo_time_t time;
    monitor_t   *monitor;
    long long   n_forks;
    int i;

    i = 0;
    while (++i < n_forks + 1)
    {
        ti[i].th = 0;
        ti[i].monitor = monitor;
        ti[i].monitor->n_forks = n_forks;
        ti[i].fork = mutex;
        ti[i].print_mutex = 0;
        ti[i].time_mutex = 0;
        ti[i].thread_id = i;
        ti[i].n_forks = ft_atol(argv[1]);
        ti[i].time_to_die = ft_atol(argv[2]);
        ti[i].time_to_eat = ft_atol(argv[3]);
        ti[i].sleep_time = ft_atol(argv[4]);
        ti[i].n_times = ft_atol(argv[5]);
        ti[i].last_meal_ms = 0;
    }
}

int     main(int argc, char *argv[])
{
    fork_tracker_t *mutex;
    philo_info_t   *ti;
    philo_time_t time;
    long long   n_forks;
    
    if (argc != 6)
        return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(fork_tracker_t));
    ti = malloc(n_forks * sizeof(philo_info_t));
    if (!ti || !mutex)
        return (0);
    struct_filler(ti, mutex, argv);
    monitor_create(ti);
}

