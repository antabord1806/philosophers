#include "../include/structs.h"
#include "../include/philo.h"


int     thread_creator(int n_forks)
{
    pthread_t *th;
    mutex_tracker_t *mutex;
    int i;

    i = 0;
    mutex = malloc(n_forks * sizeof(mutex_tracker_t));
    if (!mutex)
        return (0);
    while (i++ < n_forks)
    {
        pthread_mutex_init(&mutex[i].m, NULL);
        mutex[i]. locked = FALSE;
        i++;
        printf("mutex_criada: %d locked_status: %d\n", mutex[i].m, mutex[i].locked);
    }
    i = -1;
    th = malloc(n_forks * sizeof(pthread_t));
    if (!th)
        return (0);
    while (i++ < n_forks)
    {
        if (pthread_create(th[i], NULL, timer, NULL) != 0)
            return (printf("Errso na criação de thread\n"), 0);
        printf("thread_criada: %d\n", th[i]);
    }
    th[i] = '\0';
    i = -1;
    return (0);
}


static long long	ft_atol(char *str)
{
	long long	result;
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
	return (result * sign);
}

int     main(int argc, char *argv[])
{
    if (argc != 5)
        return (0);
    thread_creator(ft_atol(argv[1]));
}