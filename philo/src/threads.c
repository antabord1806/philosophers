#include "../include/structs.h"
#include "../include/philo.h"

static void    *eating_spaggetti(void *args)
{
    int i;
    thread_info_t *status;
    mutex_tracker_t *mutex;
    pthread_t thread;
    i = -1;

    status = (thread_info_t *)args;
    mutex = status->mutex;
    thread = status->th;
    status->status = thread;
    while (1)
    {
        if (mutex[++i].locked_status == true)
            ;
        else
        {
            mutex[i].owner = thread;
            mutex[i].locked_status = true;
            if (mutex[i++].locked_status == true)
                status->status = WAITING_1;
            else
                status->status = RUNNING;
        }
        if (status->status == WAITING_1 || status->status == RUNNING)
            return;
    }
    return (NULL);
}

static thread_info_t    starter_args(mutex_tracker_t *mutex, pthread_t thread, int i)
{
    thread_info_t *args;

    args[i].mutex = mutex;
    args[i].mutex1_id = -1;
    args[i].mutex2_id = -1;
    args[i].th = thread;
    args[i].status = -1;
    return (args);
}
int     thread_creator(mutex_tracker_t *mutex, thread_info_t *threads, thread_info_t *args, size_t n_forks)
{
    pthread_t *th;
    thread_info_t args[n_forks];
    int i;

    i = -1;
    while (i++ < n_forks)
    {
        pthread_mutex_init(&mutex[i].m, NULL);
        mutex[i].locked_status = false;
        printf("mutex_criada: %p locked_status: %d\n", (void *)&mutex[i].m, (int)mutex[i].locked_status);
        args[i] = starter_args(mutex, th[i], i);
    }
    i = -1;
    th = malloc(n_forks * sizeof(pthread_t));
    if (!th || !args)
        return (0);
    while (i++ < n_forks)
    {
        if (pthread_create(th[i], NULL, eating_spaggetti, &args[i]) != 0)
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
    thread_info_t *threads;
    long long n_forks;

    if (argc != 5)
    return (0);
    n_forks = ft_atol(argv[1]);
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    if (!mutex)
        return (0);
    threads = malloc(n_forks * sizeof(thread_info_t));
    if (!threads)
        return (0);
    thread_creator(mutex, threads, (size_t)n_forks);
    free(mutex);
    free(threads);
}