#include "philo.h"

void	*ft_test(void *s)
{
	t_data *data;

	data = (t_data *)s;

	pthread_mutex_lock(&data->mutex);
	ft_printf("incrementing the variable\n");
	data->i++;
	pthread_mutex_unlock(&data->mutex);
	
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	
	// if (argc != 5 || argc != 4)
	// 	return (free(data), 0);
	
	data->philonbr = ft_atoi(argv[1]);
	data->timetodie = ft_atoi(argv[2]);
	data->timetoeat = ft_atoi(argv[3]);
	data->timetosleep = ft_atoi(argv[4]);
	if (argc == 5)
	{
		data->philomusteat = ft_atoi(argv[5]);
	}
	
	ft_printf("number of philos : %d\n", data->philonbr);
	ft_printf("time to die : %d\n", data->timetodie);
	ft_printf("time to eat : %d\n", data->timetoeat);
	ft_printf("time to sleep : %d\n", data->timetosleep);
	if (argc == 5)
	{
		ft_printf("nbr of time philo must eat : %d\n", data->philomusteat);
	}

	
	data->i = 10;
	data->num = 0;

	// pthread_t *tabid;
	// tabid = malloc(sizeof(pthread_t) * 3);

	// pthread_mutex_init(&data->mutex, NULL);


	// pthread_create(&tabid[0], NULL, ft_test, data);
	// pthread_create(&tabid[1], NULL, ft_test, data);
	// pthread_create(&tabid[2], NULL, ft_test, data);

	// pthread_join(tabid[0], NULL);
	// pthread_join(tabid[1], NULL);
	// pthread_join(tabid[2], NULL);

	//ft_printf("%d\n", data->i);
	
	//pthread_mutex_destroy(&data->mutex);
	return (0);
}
