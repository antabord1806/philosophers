/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:54:34 by antabord          #+#    #+#             */
/*   Updated: 2025/11/23 18:54:37 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	sleeping_time(philo_info_t *pi)
{
	long	timestamp;

	pthread_mutex_lock(pi->time_mutex);
	timestamp = current_miliseconsds();
	pthread_mutex_unlock(pi->time_mutex);
	printf_msg(pi, "is sleeping");
	usleep(pi->sleep_time * 1000);
}

static void	eating_spaggeti(philo_info_t *pi, long start, long first,
		long second)
{
	long	timetstamp;

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

static void	*routine(philo_info_t *pi, long first, long second)
{
	while (1)
	{
		eating_spaggeti(pi, pi->start_time, first, second);
		sleeping_time(pi);
		pthread_mutex_lock(pi->print_mutex);
		if (pi->monitor->life_status == DEAD)
			break ;
		pthread_mutex_unlock(pi->print_mutex);
	}
	pthread_mutex_unlock(pi->print_mutex);
	return (NULL);
}

void	*setting_table(void *args)
{
	philo_info_t *pi;
	long first;
	long second;
	long tmp;

	pi = (philo_info_t *)args;
	first = pi->thread_id - 1;
	if (pi->thread_id != pi->n_forks + 1)
		second = (pi->thread_id + 1) % pi->n_forks;
	else
		second = 0;
	if (pi->thread_id % 2 == 1)
	{
		tmp = first;
		first = second;
		second = tmp;
	}
	return (routine(pi, first, second));
}