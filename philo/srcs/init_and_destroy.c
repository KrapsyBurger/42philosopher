#include <philo.h>

int	destroy_mutex(t_thread **thread, t_philo **philo)
{
	int i;
	
	i = (*philo)->philonbr;
	while (i > 0)
	{
		if (pthread_mutex_destroy(&(*thread)->mutex[i]) != 0)
			return (0);
		i--;
	}
	return (1);
}

int	init_mutex(t_thread **thread, t_philo **philo)
{
	int i;

	i = 0;
	while (i < (*philo)->philonbr)
	{
		if (pthread_mutex_init(&(*thread)->mutex[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_struct(t_philo **philo, t_thread **thread, int argc, char **argv)
{
	(*philo) = malloc(sizeof(t_philo));
	if ((*philo) == NULL)
		return (0);
	if (argc > 6 || argc < 5)
		return (0);
	(*philo)->philonbr = ft_atoi(argv[1]);
	(*philo)->timetodie = ft_atoi(argv[2]);
	(*philo)->timetoeat = ft_atoi(argv[3]);
	(*philo)->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*philo)->philomusteat = ft_atoi(argv[5]);
	(*thread) = malloc(sizeof(t_thread) * (*philo)->philonbr);
	if ((*thread) == NULL)
		return (0);
	(*thread)->mutex = malloc(sizeof(pthread_mutex_t) * (*philo)->philonbr);
	if ((*thread)->mutex == NULL)
		return (0);
	if (init_mutex(thread, philo) == 0)
		return (0);
	return (1);
}

int	ft_thread_create(t_thread **thread, t_philo **philo)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (i < (*philo)->philonbr)
	{
		pthread_create(&(*thread)[i].id, NULL, routine, (*thread));
		(*thread)[i].i = a;
		i++; 
		a++;
	}
	i--;
	while (i >= 0)
	{
		pthread_join((*thread)[i].id, NULL);
		i--;
	}
	return (0);
}