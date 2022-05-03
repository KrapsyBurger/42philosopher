#include "philo.h"

void	*ft_test(void *s)
{
	t_data *data;

	data = (t_data *)s;

	pthread_mutex_lock(&data->mutex[data->num]);
	ft_printf("incrementing the variable\n");
	data->i++;
	pthread_mutex_unlock(&data->mutex[data->num]);
	return (NULL);
}


int	ft_thread_create(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philonbr)
	{
		pthread_create(&(*data)->tabid[i], NULL, ft_test, (*data));
		i++;
		//(*data)->num++;
	}
	while (i > 0)
	{
		pthread_join((*data)->tabid[i], NULL);
		i--;
	}
	return (0);
}


int	ft_init(t_data **data, int argc, char **argv)
{
	(*data) = malloc(sizeof(t_data));

	if (argc > 6 || argc < 5)
		return (0);

	(*data)->philonbr = ft_atoi(argv[1]);
	(*data)->timetodie = ft_atoi(argv[2]);
	(*data)->timetoeat = ft_atoi(argv[3]);
	(*data)->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->philomusteat = ft_atoi(argv[5]);
	return (1);
}

int main(int argc, char **argv)
{
	t_data *data;
	
	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (ft_init(&data, argc, argv) == 0)
		return (free(data), 0);

	// ft_printf("number of philos : %d\n", data->philonbr);
	// ft_printf("time to die : %d\n", data->timetodie);
	// ft_printf("time to eat : %d\n", data->timetoeat);
	// ft_printf("time to sleep : %d\n", data->timetosleep);
	// if (argc == 6)
	// 	ft_printf("nbr of time philo must eat : %d\n", data->philomusteat);

	
	data->i = 10;
	data->num = 0;

	data->tabid = malloc(sizeof(pthread_t) * data->philonbr);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->philonbr);

	int i = 0;
	while (i < data->philonbr)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	ft_thread_create(&data);

	ft_printf("%d\n", data->i);
	
	while (i > 0)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i--;
	}
	return (0);
}
