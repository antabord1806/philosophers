/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:22:18 by antabord          #+#    #+#             */
/*   Updated: 2025/11/22 16:33:49 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void     sleeping_time(philo_info_t *pi)
{
    long   timestamp;

    pthread_mutex_lock(pi->time_mutex);
    timestamp = current_miliseconsds();
    pthread_mutex_unlock(pi->time_mutex);
    printf_msg(pi, "is sleeping");
    usleep(pi->sleep_time * 1000);
}

static void     eating_spaggeti(philo_info_t *pi, long start, long first, long second)
{
    long timetstamp;

    printf_msg(pi, "is thinking");
    pthread_mutex_lock(&pi->fork[first].m);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds();
    pthread_mutex_unlock(pi->time_mutex);
    printf_msg(pi, "has taken a fork");
    pthread_mutex_lock(&pi->fork[second].m);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds();
    pthread_mutex_unlock(pi->time_mutex);
    printf_msg(pi, "has taken a fork");
    printf_msg(pi, "is eating");
    usleep(pi->time_to_eat * 1000);
    pthread_mutex_lock(pi->time_mutex);
    timetstamp = current_miliseconsds() - start;
    pi->last_meal_ms = timetstamp;
    pthread_mutex_unlock(pi->time_mutex);
    pthread_mutex_unlock(&pi->fork[first].m);
    pthread_mutex_unlock(&pi->fork[second].m);
    return ;
}

static void    *pantry(void *args)
{
    philo_info_t   *pi;
    long first;
    long second;
    long    tmp;

    pi = (philo_info_t *)args;
    first = pi->thread_id;
    if (pi->thread_id != pi->n_forks)
        second = (pi->thread_id + 1) % pi->n_forks;
    else 
        second = 0;
    if (pi->thread_id % 2 == 1)
    {
        tmp = first;
        first = second;
        second = tmp;
    }
    while (1)
    {
        eating_spaggeti(pi, pi->start_time, first, second);
        sleeping_time(pi);
        pthread_mutex_lock(pi->print_mutex);
        if (pi->monitor->life_status == DEAD)
            break;
        pthread_mutex_unlock(pi->print_mutex);
    }
    pthread_mutex_unlock(pi->print_mutex);
    return NULL;
}

int     philo_creator(philo_info_t *ti)
{
    int i;
    
    i = -1;
    while (++i < ti->n_forks)
    {
        pthread_mutex_init(&ti->fork[i].m, NULL);
        //printf("mutex criada: %p\n", (void *)&ti->fork[i].m);
    }
    i = -1;
    while (++i < ti->n_forks)
    {
        if (pthread_create(&ti[i].th, NULL, pantry, &ti[i]) != 0)
            printf("ERROR grabbing fork\n");
        usleep (5000);
        //printf("thread criada: %d\n", ti[i].thread_id);
    }
    return (0);
}


static long	ft_atol(char *str)
{
    long	result;
    long   total;
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

monitor_t    *struct_filler(philo_info_t *ti, fork_tracker_t *mutex, char *argv[], long n_forks)
{
    monitor_t   *monitor;
    long        i;
    long        id;

    monitor = malloc(sizeof(monitor_t));
    if (!monitor)
        return (NULL);
    monitor->pi = ti;
    monitor->n_forks = n_forks;
    monitor->life_status = ALIVE;
    monitor->last_meal_monitor = malloc(sizeof(pthread_mutex_t) * n_forks);
    if (!monitor->last_meal_monitor
        || pthread_mutex_init(&monitor->print_mutex, NULL)
        || pthread_mutex_init(&monitor->time_mutex, NULL))
        return (free(monitor->last_meal_monitor), free(monitor), NULL);
    i = -1;
    while (++i < n_forks)
        pthread_mutex_init(&monitor->last_meal_monitor[i], NULL);
    i = -1;
    id = i + 1;
    while (++i < n_forks)
    {
        ti[i].monitor = monitor;
        ti[i].fork = mutex;
        ti[i].print_mutex = &monitor->print_mutex;
        ti[i].time_mutex = &monitor->time_mutex;
        ti[i].thread_id = i;
        ti[i].n_forks = (int)n_forks;
        ti[i].time_to_die = ft_atol(argv[2]);
        ti[i].time_to_eat = ft_atol(argv[3]);
        ti[i].sleep_time = ft_atol(argv[4]);
        ti[i].n_times = ft_atol(argv[5]);
        ti[i].start_time = current_miliseconsds();
        ti[i].last_meal_ms = 0;
    }
    return (monitor);
}

int     main(int argc, char *argv[])
{
    fork_tracker_t *mutex;
    philo_info_t   *ti;
    long   n_forks;
    int     i;
    
    i = -1;
    if (argc != 6)
        return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(fork_tracker_t));
    ti = malloc(n_forks * sizeof(philo_info_t));
    if (!ti || !mutex)
        return (0);
    memset(ti, 0, sizeof(philo_info_t) * n_forks);
    memset(mutex, 0, sizeof(fork_tracker_t) * n_forks);
    if (!struct_filler(ti, mutex, argv, n_forks))
        return (free(mutex), free(ti), 0);
    philo_creator(ti);
    if (pthread_create(&ti->monitor->monitor, NULL, life_check, ti->monitor) != 0)
        return (printf("failed to create monitor thread\n"), 0);
    funeral(ti);
    return (free(mutex), free(ti), 0);
}

