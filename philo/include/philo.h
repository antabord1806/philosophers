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

int			funeral(philo_info_t *pi);
void		*life_check(void *arg);
void		printf_msg(philo_info_t *pi, long timestamp, const char *msg);
long		current_miliseconsds(void);
monitor_t	*monitor_starter(philo_info_t *ti, fork_tracker_t *mutex,
				char *argv[], long n_forks);
monitor_t	*struct_filler(philo_info_t *ti, fork_tracker_t *mutex,
				monitor_t *monitor, char *argv[]);
long		ft_atol(char *str);
void		*setting_table(void *args);
void		meal_check(monitor_t *mon, int i);
void		single_philo(philo_info_t *pi, fork_tracker_t *mutex,
				char *death_time);

#endif