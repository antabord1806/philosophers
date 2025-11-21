#include "../include/structs.h"
#include "../include/philo.h"
#include <unistd.h>

long long   current_miliseconsds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void *life_check(void *arg)
{
    monitor_t *mon;
    long long   timestamp;
    int i;

    i = 0;
    mon = (monitor_t *)arg;
    while (mon->life_status == ALIVE)
    {
        if (i == mon->n_forks)
            i = 0;
        pthread_mutex_lock(mon->time);
        timestamp = current_miliseconsds() - mon->pi[i].start_time;
        if (timestamp > mon->pi->time_to_die)
        {
            mon->life_status = DEAD;
            pthread_mutex_lock(mon->print_mutex);
            printf("%lld philo %d has died\n", timestamp, mon->pi[i].thread_id);
            pthread_mutex_unlock(mon->print_mutex);
            funeral(mon, mon->pi);
        }
        i++;
    }
    return (NULL);
}

int    monitor_create(philo_info_t *pi)
{
    int i;

    i = -1;
    if (pthread_mutex_init(pi->print_mutex, NULL) != 0 || pthread_mutex_init(pi->time_mutex, NULL) != 0)
        return(printf("print mutex or getting time mutex init failed\n"), free(pi->fork), free(pi), 0);
        while (++i != pi->n_forks)
        {
            if (pthread_mutex_init(&pi->monitor->last_meal_monitor[i], NULL) != 0)
                return(printf("print mutex or getting last_meal_monitor init failed\n"), free(pi->fork), free(pi), 0);
        }
        if (pthread_create(&pi->monitor->monitor, NULL, life_check, pi->monitor) != 0)
            return (printf("failed to create monitor thread\n"), 0);
        i = -1;
        while (++i < pi->n_forks)
        {
            pthread_join(pi[i].th, NULL);
            pthread_mutex_destroy(&pi[i]);
            pthread_mutex_destroy(&pi->print_mutex);
            pthread_mutex_destroy(&pi->time_mutex);
        }
        return 1;
}
