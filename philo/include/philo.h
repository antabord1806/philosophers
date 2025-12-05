/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:10:19 by antabord          #+#    #+#             */
/*   Updated: 2025/12/05 16:53:06 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../include/structs.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

int			funeral(t_philo_info *pi);
void		*life_check(void *arg);
void		printf_msg(t_philo_info *pi, long timestamp, const char *msg);
long		current_miliseconds(void);
t_monitor	*monitor_starter(t_philo_info *ti, t_fork_tracker *mutex,
				char *argv[], long n_forks);
t_monitor	*struct_filler(t_philo_info *ti, t_fork_tracker *mutex,
				t_monitor *monitor, char *argv[]);
long		ft_atol(char *str);
void		*setting_table(void *args);
void		meal_check(t_philo_info *pi);
void		single_philo(t_philo_info *pi, t_fork_tracker *mutex,
				long death_time, bool ola);

#endif