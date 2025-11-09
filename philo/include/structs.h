#ifndef STRUCTS_H
#define STRUCTS_H

#include "philo.h"

typedef struct s_mutexes
{
    pthread_mutex_t m;
    pthread_t owner;
    bool locked;
}   mutex_tracker_t;

#endif