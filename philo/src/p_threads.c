/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_threads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:22:18 by antabord          #+#    #+#             */
/*   Updated: 2025/11/28 16:11:26 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_creator(t_philo_info *ti)
{
	int	i;

	i = -1;
	while (++i < ti->n_forks)
		pthread_mutex_init(&ti->fork[i].m, NULL);
	i = -1;
	while (++i < ti->n_forks)
	{
		if (ti->thread_id % 2 == 0)
			usleep(100);
		if (pthread_create(&ti[i].th, NULL, setting_table, &ti[i]) != 0)
			printf("ERROR grabbing fork\n");
	}
	return (0);
}

t_monitor	*struct_filler(t_philo_info *ti, t_fork_tracker *mutex,
		t_monitor *monitor, char *argv[])
{
	int	i;

	i = -1;
	while (++i < mutex->n_forks)
	{
		ti[i].fork = mutex;
		ti[i].monitor = monitor;
		ti[i].print_mutex = &monitor->print_mutex;
		ti[i].time_mutex = &monitor->time_mutex;
		ti[i].state_mutex = &monitor->state_mutex;
		ti[i].last_meal_monitor = &monitor->last_meal_monitor;
		ti[i].thread_id = i;
		ti[i].n_forks = (int)mutex->n_forks;
		ti[i].time_to_die = ft_atol(argv[2]);
		ti[i].time_to_eat = ft_atol(argv[3]);
		ti[i].sleep_time = ft_atol(argv[4]);
		if (argv[5] && ft_atol(argv[5]) == 0)
			single_philo(ti, mutex, ti[i].time_to_die, false);
		else if (!argv[5])
			ti[i].amount_of_meals = -1;
		else
			ti[i].amount_of_meals = ft_atol(argv[5]);
		ti[i].last_meal_ms = current_miliseconds();
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
	t_fork_tracker	*mutex;
	t_philo_info	*ti;

	if (argc > 6 || argc < 5)
		return (0);
	if (!ft_atol(argv[1]))
		return (0);
	mutex = malloc(ft_atol(argv[1]) * sizeof(t_fork_tracker));
	ti = malloc(ft_atol(argv[1]) * sizeof(t_philo_info));
	if (!ti || !mutex)
		return (0);
	memset(ti, 0, sizeof(t_philo_info) * (int)ft_atol(argv[1]));
	if (ft_atol(argv[1]) < 2)
		single_philo(ti, mutex, ft_atol(argv[2]), true);
	if (!monitor_starter(ti, mutex, argv, ft_atol(argv[1])))
		return (free(mutex), free(ti), 0);
	philo_creator(ti);
	if (pthread_create(&ti->monitor->monitor, NULL, life_check,
			ti->monitor) != 0)
		return (printf("failed to create monitor thread\n"), 0);
	funeral(ti);
	return (free(mutex), free(ti), 0);
}
