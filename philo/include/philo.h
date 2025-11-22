#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../include/structs.h"

int    funeral(philo_info_t *pi);
void *life_check(void *arg);
void    printf_msg(philo_info_t *pi, const char *msg);
long   current_miliseconsds(void);

#endif