/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_meal_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:43:37 by antabord          #+#    #+#             */
/*   Updated: 2025/11/27 18:16:58 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	meal_check(t_monitor *mon, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&mon->last_meal_monitor);
	time_since_last_meal = current_miliseconsds() - mon->pi[i].last_meal_ms;
	pthread_mutex_unlock(&mon->last_meal_monitor);
	if (time_since_last_meal > mon->pi[i].time_to_die)
	{
		pthread_mutex_lock(&mon->state_mutex);
		mon->life_status = DEAD;
		pthread_mutex_unlock(&mon->state_mutex);
		pthread_mutex_lock(&mon->print_mutex);
		printf("%ld philo %d has died\n", current_miliseconsds(),
			mon->pi[i].thread_id);
		pthread_mutex_unlock(&mon->print_mutex);
	}
	pthread_mutex_lock(&mon->last_meal_monitor);
	if (mon->pi[i].amount_of_meals == mon->pi[i].current_meal)
	{
		pthread_mutex_lock(&mon->state_mutex);
		mon->meal_status = FULL;
		pthread_mutex_unlock(&mon->state_mutex);
	}
	pthread_mutex_unlock(&mon->last_meal_monitor);
	return ;
}
