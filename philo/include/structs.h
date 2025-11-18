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

typedef struct s_time
{
    long long   start_time;
    long long   time_to_eat;
    long long   end_time;
    long long   time_to_die;
    long long   sleep_time;
    long long   n_times;
    long long   wait_time;
}   philo_time_t;
typedef struct s_thread_info
{
    pthread_t   th;
    mutex_tracker_t *fork;
    philo_time_t  *time;
    int     status;
    int     thread_id;
    int     n_forks;
    bool    life_status;
}   thread_info_t;



#endif