/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_meal_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:43:37 by antabord          #+#    #+#             */
/*   Updated: 2025/12/05 18:08:03 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	meal_check(t_philo_info *pi)
{
    long	now;
    long	death_ms;

    pthread_mutex_lock(pi->last_meal_monitor);
    now = current_miliseconds();
    death_ms = pi->last_meal_ms + pi->time_to_die;
    pthread_mutex_unlock(pi->last_meal_monitor);
    if (now >= death_ms)
    {
        pthread_mutex_lock(pi->state_mutex);
        if (pi->monitor->life_status == ALIVE)
        {
            pi->monitor->life_status = DEAD;
            pthread_mutex_unlock(pi->state_mutex);
            pthread_mutex_lock(pi->print_mutex);
            printf("%ld philo %d has died\n", death_ms, pi->thread_id);
            pthread_mutex_unlock(pi->print_mutex);
        }
        else
            pthread_mutex_unlock(pi->state_mutex);
        return ;
    }
    pthread_mutex_lock(pi->state_mutex);
    if (pi->amount_of_meals >= 0 && pi->current_meal >= pi->amount_of_meals)
        pi->monitor->meal_status = FULL;
    pthread_mutex_unlock(pi->state_mutex);
}
