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
    long long start_time;
    long long time_to_eat;
}   mutex_tracker_t;


typedef struct s_forks
{
    int     fork_id;
}   t_forks;
typedef struct s_thread_info
{
    pthread_t   th;
    mutex_tracker_t *fork;
    int     status;
    int     thread_id;
    int     n_forks;
    bool    life_status;
    long long   start_time;
    long long   time_to_die;
    long long   sleep_time;
    long long   number_of_times_to_eat;
    long long   wait_time;
}   thread_info_t;

#endif