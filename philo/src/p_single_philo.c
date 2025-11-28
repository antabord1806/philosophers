/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_single_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:43:50 by antabord          #+#    #+#             */
/*   Updated: 2025/11/28 16:04:38 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	single_philo(t_philo_info *pi, t_fork_tracker *mutex, long death_time,
		bool ola)
{
	long	start;

	if (ola == true)
	{
		start = current_miliseconds();
		printf("%ld philo 0 is thinking\n", start);
		usleep(death_time * 1000);
		printf("%ld philo 0 has died\n", current_miliseconds());
		return (free(mutex), free(pi), exit(127));
	}
	else
	{
		start = current_miliseconds();
		printf("%ld philo 0 is thinking\n", start);
		printf("%ld philo 0 has taken a fork\n", current_miliseconds());
		printf("%ld philo 0 has taken a fork\n", current_miliseconds());
		usleep(death_time * 1000);
		printf("%ld philo 0 has died\n", current_miliseconds());
		pthread_mutex_destroy(pi->state_mutex);
		pthread_mutex_destroy(pi->print_mutex);
		pthread_mutex_destroy(pi->time_mutex);
		return (free(mutex), free(pi->monitor), free(pi), exit(1));
	}
}
