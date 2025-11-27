/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:54:34 by antabord          #+#    #+#             */
/*   Updated: 2025/11/27 19:08:27 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	sleeping_time(t_philo_info *pi)
{
	long	timestamp;

	pthread_mutex_lock(pi->time_mutex);
	timestamp = current_miliseconsds();
	pthread_mutex_unlock(pi->time_mutex);
	printf_msg(pi, timestamp, "is sleeping");
	usleep(pi->sleep_time * 1000);
}

static void	grabbing_forks(t_philo_info *pi, long first, long second)
{
	long	timetstamp;

	pthread_mutex_lock(pi->time_mutex);
	timetstamp = current_miliseconsds();
	pi->start_time = timetstamp;
	pthread_mutex_unlock(pi->time_mutex);
	printf_msg(pi, timetstamp, "is thinking");
	pthread_mutex_lock(&pi->fork[first].m);
	pthread_mutex_lock(pi->time_mutex);
	timetstamp = current_miliseconsds();
	pthread_mutex_unlock(pi->time_mutex);
	printf_msg(pi, timetstamp, "has taken a fork");
	pthread_mutex_lock(&pi->fork[second].m);
	pthread_mutex_lock(pi->time_mutex);
	timetstamp = current_miliseconsds();
	pthread_mutex_unlock(pi->time_mutex);
	printf_msg(pi, timetstamp, "has taken a fork");
	printf_msg(pi, timetstamp, "is eating");
}

static void	eating_spaggeti(t_philo_info *pi, long first, long second)
{
	grabbing_forks(pi, first, second);
	pthread_mutex_lock(pi->last_meal_monitor);
	pi->last_meal_ms = current_miliseconsds();
	pthread_mutex_unlock(pi->last_meal_monitor);
	usleep(pi->time_to_eat * 1000);
	pthread_mutex_unlock(&pi->fork[second].m);
	pthread_mutex_unlock(&pi->fork[first].m);
	return ;
}

static void	*routine(t_philo_info *pi, long first, long second, int completed)
{
	while (1)
	{
		pthread_mutex_lock(pi->state_mutex);
		if (pi->monitor->life_status == DEAD
			|| pi->monitor->meal_status == FULL)
			break ;
		pthread_mutex_unlock(pi->state_mutex);
		eating_spaggeti(pi, first, second);
		sleeping_time(pi);
		pthread_mutex_lock(pi->last_meal_monitor);
		pi->current_meal++;
		pthread_mutex_unlock(pi->last_meal_monitor);
		if (completed)
		{
			pthread_mutex_lock(pi->state_mutex);
			if (pi->monitor->finished_count < pi->monitor->n_forks)
				pi->monitor->finished_count++;
			if (pi->monitor->finished_count == pi->monitor->n_forks)
				pi->monitor->meal_status = FULL;
			pthread_mutex_unlock(pi->state_mutex);
			break ;
		}
	}
	pthread_mutex_unlock(pi->state_mutex);
	return (NULL);
}

void	*setting_table(void *args)
{
	t_philo_info	*pi;
	long			first;
	long			second;
	long			temp;
	int				completed;

	pi = (t_philo_info *)args;
	first = pi->thread_id;
	if (pi->thread_id + 1 != pi->n_forks)
		second = (pi->thread_id + 1) % pi->n_forks;
	else
		second = 0;
	if (first > second)
	{
		temp = first;
		first = second;
		second = temp;
	}
	completed = (pi->amount_of_meals > 0
			&& pi->current_meal >= pi->amount_of_meals);
	return (routine(pi, first, second, completed));
}
