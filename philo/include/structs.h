#ifndef STRUCTS_H
#define STRUCTS_H

#include "philo.h"

#define WAITING_0   0 //0 mutexes
#define WAITING_1   1 //1 mutex
#define RUNNING     2 //2 mutexes

typedef struct s_mutexes
{
    pthread_mutex_t m;
    pthread_t owner;
    bool locked_status;
}   mutex_tracker_t;

typedef struct s_thread_info
{
    pthread_t   th;
    mutex_tracker_t *mutex;
    int     mutex1_id;
    int     mutex2_id;
    int     status;
    int     n_forks;
}   thread_info_t;

#endif