/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:21:20 by antabord          #+#    #+#             */
/*   Updated: 2025/11/23 18:50:47 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	current_miliseconsds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	printf_msg(philo_info_t *pi, const char *msg)
{
	pthread_mutex_lock(pi->print_mutex);
	if (pi->monitor->life_status == ALIVE)
		printf("%ld philo %d %s\n", current_miliseconsds(), pi->thread_id, msg);
	pthread_mutex_unlock(pi->print_mutex);
}

int	funeral(philo_info_t *pi)
{
	int	i;

	i = -1;
	while (++i < pi->n_forks)
		pthread_join(pi[i].th, NULL);
	pthread_join(pi->monitor->monitor, NULL);
	i = -1;
	while (++i < pi->n_forks)
		pthread_mutex_destroy(&pi->fork[i].m);
	pthread_mutex_destroy(pi->print_mutex);
	pthread_mutex_destroy(pi->time_mutex);
	i = -1;
	while (++i < pi->n_forks)
		pthread_mutex_destroy(&pi->monitor->last_meal_monitor[i]);
	return (free(pi->monitor->last_meal_monitor), free(pi->monitor), 0);
}

void	*life_check(void *arg)
{
	monitor_t	*mon;
	long		timestamp;
	int			i;

	i = 0;
	mon = (monitor_t *)arg;
	while (1)
	{
		if (i == mon->n_forks)
			i = 0;
		pthread_mutex_lock(&mon->time_mutex);
		timestamp = current_miliseconsds();
		if ((current_miliseconsds() - (mon->pi[i].start_time
					+ mon->pi[i].last_meal_ms)) > mon->pi[i].time_to_die)
		{
			pthread_mutex_lock(&mon->print_mutex);
			mon->life_status = DEAD;
			printf("%ld philo %d has died\n", timestamp, mon->pi[i].thread_id);
			pthread_mutex_unlock(&mon->print_mutex);
			pthread_mutex_unlock(&mon->time_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&mon->time_mutex);
		i++;
	}
	return (NULL);
}

monitor_t	*monitor_starter(philo_info_t *ti, fork_tracker_t *mutex,
		char *argv[], long n_forks)
{
	monitor_t	*monitor;
	long		i;

	monitor = malloc(sizeof(monitor_t));
	if (!monitor)
		return (NULL);
	monitor->pi = ti;
	monitor->n_forks = n_forks;
	monitor->life_status = ALIVE;
	monitor->last_meal_monitor = malloc(sizeof(pthread_mutex_t) * n_forks);
	if (!monitor->last_meal_monitor || pthread_mutex_init(&monitor->print_mutex,
			NULL) || pthread_mutex_init(&monitor->time_mutex, NULL))
		return (free(monitor->last_meal_monitor), free(monitor), NULL);
	i = -1;
	while (++i < n_forks)
		pthread_mutex_init(&monitor->last_meal_monitor[i], NULL);
	mutex->n_forks = n_forks;
	return (struct_filler(ti, mutex, monitor, argv));
}
