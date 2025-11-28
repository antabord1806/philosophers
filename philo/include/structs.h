/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:10:27 by antabord          #+#    #+#             */
/*   Updated: 2025/11/28 15:20:51 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>

# define WAITING_0 0 // 0 mutexes
# define WAITING_1 1 // 1 mutex
# define RUNNING 2   // 2 mutexes

# define ALIVE 0 // alive
# define DEAD 1  // dead

# define HUNGRY 0 // alive
# define FULL 1   // dead

typedef struct s_forks		t_fork_tracker;
typedef struct s_monitor	t_monitor;
typedef struct s_philo_info	t_philo_info;

struct						s_forks
{
	pthread_mutex_t			m;
	int						n_forks;
	bool					locked_status;
};

struct						s_monitor
{
	pthread_t				monitor;
	t_philo_info			*pi;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			time_mutex;
	pthread_mutex_t			state_mutex;
	pthread_mutex_t			last_meal_monitor;
	long					n_forks;
	int						finished_count;
	bool					life_status;
	bool					meal_status;
};

struct						s_philo_info
{
	pthread_t				th;
	t_monitor				*monitor;
	t_fork_tracker			*fork;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			*time_mutex;
	pthread_mutex_t			*state_mutex;
	pthread_mutex_t			*last_meal_monitor;
	int						thread_id;
	int						n_forks;
	long					time_to_eat;
	long					end_time;
	long					time_to_die;
	long					sleep_time;
	long					n_times;
	long					wait_time;
	long					start_time;
	long					last_meal_ms;
	int						amount_of_meals;
	int						current_meal;
};

#endif