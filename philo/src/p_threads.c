/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_threads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:22:18 by antabord          #+#    #+#             */
/*   Updated: 2025/11/25 21:38:53 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_creator(philo_info_t *ti)
{
	int	i;

	i = -1;
	while (++i < ti->n_forks)
	{
		pthread_mutex_init(&ti->fork[i].m, NULL);
	}
	i = -1;
	while (++i < ti->n_forks)
	{
		if (ti->thread_id % 2 == 0)
			usleep(1000);
		if (pthread_create(&ti[i].th, NULL, setting_table, &ti[i]) != 0)
			printf("ERROR grabbing fork\n");
	}
	return (0);
}

monitor_t	*struct_filler(philo_info_t *ti, fork_tracker_t *mutex,
		monitor_t *monitor, char *argv[])
{
	int	i;
	int	n_forks;

	i = -1;
	n_forks = mutex->n_forks;
	while (++i < n_forks)
	{
		ti[i].monitor = monitor;
		ti[i].fork = mutex;
		ti[i].print_mutex = &monitor->print_mutex;
		ti[i].time_mutex = &monitor->time_mutex;
		ti[i].state_mutex = &monitor->state_mutex;
		ti[i].last_meal_monitor = &monitor->last_meal_monitor;
		ti[i].thread_id = i;
		ti[i].n_forks = (int)n_forks;
		ti[i].time_to_die = ft_atol(argv[2]);
		ti[i].time_to_eat = ft_atol(argv[3]);
		ti[i].sleep_time = ft_atol(argv[4]);
		ti[i].amount_of_meals = ft_atol(argv[5]);
		ti[i].last_meal_ms = current_miliseconsds();
		ti[i].current_meal = 0;
	}
	return (monitor);
}

long	ft_atol(char *str)
{
	long	result;
	long	total;
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

int	main(int argc, char *argv[])
{
	fork_tracker_t	*mutex;
	philo_info_t	*ti;
	long			n_forks;

	if (argc != 6)
		return (0);
	n_forks = ft_atol(argv[1]);
	if (!ft_atol(argv[1]))
		return (0);
	mutex = malloc(n_forks * sizeof(fork_tracker_t));
	ti = malloc(n_forks * sizeof(philo_info_t));
	if (!ti || !mutex)
		return (0);
	if (n_forks == 1)
		single_philo(ti, mutex, argv[2]);
	memset(ti, 0, sizeof(philo_info_t) * n_forks);
	memset(mutex, 0, sizeof(fork_tracker_t) * n_forks);
	if (!monitor_starter(ti, mutex, argv, n_forks))
		return (free(mutex), free(ti), 0);
	philo_creator(ti);
	if (pthread_create(&ti->monitor->monitor, NULL, life_check,
			ti->monitor) != 0)
		return (printf("failed to create monitor thread\n"), 0);
	funeral(ti);
	return (free(mutex), free(ti), 0);
}
