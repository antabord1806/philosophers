/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_single_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:43:50 by antabord          #+#    #+#             */
/*   Updated: 2025/11/25 21:44:59 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	single_philo(philo_info_t *pi, fork_tracker_t *mutex, char *death_time)
{
	long	start;

	start = current_miliseconsds();
	printf("%ld philo 0 is thinking\n", start);
	usleep(ft_atol(death_time) * 1000);
	printf("%ld philo 0 has died\n", current_miliseconsds());
	return (free(mutex), free(pi), exit(127));
}
