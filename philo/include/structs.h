#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>

# define WAITING_0 0 // 0 mutexes
# define WAITING_1 1 // 1 mutex
# define RUNNING 2   // 2 mutexes

# define ALIVE 0 // alive
# define DEAD 1  // dead

typedef struct s_forks		fork_tracker_t;
typedef struct s_monitor	monitor_t;
typedef struct s_philo_info	philo_info_t;

struct						s_forks
{
	pthread_mutex_t			m;
	int						n_forks;
	bool					locked_status;
};

struct						s_monitor
{
	pthread_t				monitor;
	philo_info_t			*pi;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			time_mutex;
	pthread_mutex_t			*last_meal_monitor;
	long					n_forks;
	bool					life_status;
};

struct						s_philo_info
{
	pthread_t				th;
	monitor_t				*monitor;
	fork_tracker_t			*fork;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			*time_mutex;
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
};

#endif