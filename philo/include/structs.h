#ifndef STRUCTS_H
#define STRUCTS_H

#include "philo.h"

#define WAITING_0   0 //0 mutexes
#define WAITING_1   1 //1 mutex
#define RUNNING     2 //2 mutexes

#define ALIVE       0 //alive
#define DEAD        1 //dead

typedef struct s_mutexes
{
    pthread_mutex_t m;
    pthread_t owner;
    bool locked_status;
}   mutex_tracker_t;

typedef struct s_monitor
{
    philo_info_t *ti;
}
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
    mutex_tracker_t *fork;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *time_mutex;
    philo_time_t  *time;
    int     thread_id;
    int     n_forks;
    long long last_meal_ms;
}   philo_info_t;

typedef struct s_helper_struct
{
    pthread_t   monitor;
    mutex_tracker_t     *mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t time_mutex;
    philo_time_t    *time;
    int n_forks;
}   helper_struct_t;

#endif