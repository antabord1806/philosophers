#ifndef STRUCTS_H
#define STRUCTS_H

#include "philo.h"

#define WAITING_0   0 //0 mutexes
#define WAITING_1   1 //1 mutex
#define RUNNING     2 //2 mutexes

#define ALIVE       0 //alive
#define DEAD        1 //dead

typedef struct s_forks
{
    pthread_mutex_t m;
    pthread_t owner;
    bool locked_status;
}   fork_tracker_t;

typedef struct s_monitor
{
    pthread_t   monitor;
    philo_info_t    *pi;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *time_mutex;
    pthread_mutex_t *last_meal_monitor;
    philo_time_t    *time;
    long long     n_forks;
    bool    life_status;
}   monitor_t;

typedef struct s_time
{
    long long   time_to_eat;
    long long   end_time;
    long long   time_to_die;
    long long   sleep_time;
    long long   n_times;
    long long   wait_time;
}   philo_time_t;

typedef struct s_philo_info
{
    pthread_t   th;
    monitor_t   *monitor;
    fork_tracker_t *fork;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *time_mutex;
    philo_time_t  *time;
    int     thread_id;
    int     n_forks;
    long long   time_to_eat;
    long long   end_time;
    long long   time_to_die;
    long long   sleep_time;
    long long   n_times;
    long long   wait_time;
    long long   start_time;
    long long last_meal_ms;
}   philo_info_t;

#endif