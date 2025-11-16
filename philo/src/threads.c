#include "../include/structs.h"
#include "../include/philo.h"

static void    *eating_spaggetti(void *args)
{
    thread_info_t   *thread_info;
    int i;

    i = 1;
    thread_info = (thread_info_t *)args;
    while (1)
    {
        if (thread_info->mutex[i].locked_status == true)
            i++;
        else
        {
            pthread_mutex_lock(&thread_info->mutex[i].m);
            thread_info->status = WAITING_1;
            thread_info->mutex[i].owner = thread_info->th;
            thread_info->mutex[i].locked_status = true;
            printf("thread: %p bloqueou mutex: %p locked_status: %d\n", (void *)thread_info->th, (void *)&thread_info->mutex[i].m, (int)thread_info->mutex[i].locked_status);
            i++;
            if (thread_info->mutex[i].locked_status == true)
                return NULL;
            else if (thread_info->mutex[i].locked_status == false)
            {
                pthread_mutex_lock(&thread_info->mutex[i].m);
                thread_info->status = RUNNING;
                thread_info->mutex[i].owner = thread_info->th;
                thread_info->mutex[i].locked_status = true;
                printf("thread: %p bloqueou mutex: %p locked_status: %d\n", (void *)thread_info->th, (void *)&thread_info->mutex[i].m, (int)thread_info->mutex[i].locked_status);
                return NULL;
            }
        }
        i++;
    }
}

static thread_info_t    starter_args(mutex_tracker_t *mutex, pthread_t thread, thread_info_t *args, int i)
{
    args[i].mutex = mutex;
    args[i].mutex1_id = -1;
    args[i].mutex2_id = -1;
    args[i].th = thread;
    args[i].status = WAITING_0;
    return (*args);
}
int     thread_creator(mutex_tracker_t *mutex, int n_forks)
{
    pthread_t *th;
    thread_info_t args[n_forks];
    int i;

    i = -1;
    th = malloc(n_forks * sizeof(pthread_t));
    if (!th)
        return (0);
    while (++i < n_forks)
    {
        pthread_mutex_init(&mutex[i].m, NULL);
        mutex[i].locked_status = false;
        printf("mutex_criada: %p locked_status: %d\n", (void *)&mutex[i].m, (int)mutex[i].locked_status);
        args[i] = starter_args(mutex, th[i] ,args, i);
    }
    i = -1;
    while (++i < n_forks)
    {
        if (pthread_create(&th[i], NULL, eating_spaggetti, &args[i]) != 0)
            return (printf("Errso na criação de thread\n"), free(th), 0);
        printf("thread_criada: %p\n", (void *)th[i]);
    }
    th[i] = '\0';
    free(th);
    return (0);
}


static long long	ft_atol(char *str)
{
	long long	result;
    long long   total;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
    total = result * sign;
    if (total < 0)
        return (0);
    else
	    return (total);
}

int     main(int argc, char *argv[])
{
    mutex_tracker_t *mutex;
   // thread_info_t *threads;
    long long n_forks;

    if (argc != 5)
    return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    /* threads = malloc(n_forks * sizeof(thread_info_t));
    if (!mutex || !threads)
        return (0); */
    thread_creator(mutex, (int)n_forks);
    free(mutex);
    //free(threads);
}