/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:21:20 by antabord          #+#    #+#             */
/*   Updated: 2025/11/27 18:34:47 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	current_miliseconsds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	printf_msg(t_philo_info *pi, long timestamp, const char *msg)
{
	int	alive;

	pthread_mutex_lock(pi->state_mutex);
	alive = pi->monitor->life_status == ALIVE;
	pthread_mutex_unlock(pi->state_mutex);
	if (!alive)
		return ;
	pthread_mutex_lock(pi->print_mutex);
	printf("%ld philo %d %s\n", timestamp, pi->thread_id, msg);
	pthread_mutex_unlock(pi->print_mutex);
}

int	funeral(t_philo_info *pi)
{
	int	i;

	i = -1;
	while (++i < pi->n_forks)
		pthread_join(pi[i].th, NULL);
	pthread_join(pi->monitor->monitor, NULL);
	i = -1;
	while (++i < pi->n_forks)
		pthread_mutex_destroy(&pi->fork[i].m);
	pthread_mutex_destroy(pi->state_mutex);
	pthread_mutex_destroy(pi->print_mutex);
	pthread_mutex_destroy(pi->time_mutex);
	return (free(pi->monitor), 0);
}

void	*life_check(void *arg)
{
	t_monitor	*mon;
	int			i;
	int			k;

	i = 0;
	k = 0;
	mon = (t_monitor *)arg;
	while (1)
	{
		if (i == mon->n_forks)
			i = 0;
		meal_check(mon, i);
		pthread_mutex_lock(&mon->state_mutex);
		if (mon->life_status == DEAD || mon->meal_status == FULL)
		{
			pthread_mutex_unlock(&mon->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&mon->state_mutex);
		i = (i + 1) % mon->n_forks;
		usleep(1000);
	}
	return (NULL);
}

t_monitor	*monitor_starter(t_philo_info *ti, t_fork_tracker *mutex,
		char *argv[], long n_forks)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->pi = ti;
	monitor->n_forks = n_forks;
	monitor->finished_count = 0;
	monitor->meal_status = HUNGRY;
	monitor->life_status = ALIVE;
	if (pthread_mutex_init(&monitor->print_mutex, NULL)
		|| pthread_mutex_init(&monitor->time_mutex, NULL)
		|| pthread_mutex_init(&monitor->state_mutex, NULL)
		|| pthread_mutex_init(&monitor->last_meal_monitor, NULL))
		return (free(monitor), NULL);
	mutex->n_forks = n_forks;
	return (struct_filler(ti, mutex, monitor, argv));
}
