#include "philo.h"

void	*ft_test(void *s)
{
	t_dataa *dataa;
	dataa = (t_dataa *)s;
	int i;
	i = 0;
	int l;
	//ft_printf("ceci est le thread no : %d\n", dataa[i].i);
	pthread_mutex_lock(&dataa->mutex[i]);
	//ft_printf("incrementing the variable\n");
	ft_printf("ceci est le thread no : %d\n", dataa[dataa->b].i);
	dataa->nb++;
	l = i;
	dataa->b++;
	pthread_mutex_unlock(&dataa->mutex[l]);
	return (NULL);
}

int	ft_thread_create(t_dataa **dataa, t_data **data)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (i < (*data)->philonbr)
	{
		pthread_create(&(*dataa)[i].id, NULL, ft_test, (*dataa));
		(*dataa)[i].i = a;
		//ft_printf("ceci est a : %d\n", (*dataa)[i].i);
		i++; 
		a++;
		//ft_printf("ceci est a : %d\n", (*dataa)[i].i);
	}
	i--;
	while (i >= 0)
	{
		pthread_join((*dataa)[i].id, NULL);
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
	t_dataa *dataa;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (ft_init(&data, argc, argv) == 0)
		return (free(data), 0);

	//ft_printf("data->philonbr = %d\n", data->philonbr);
	dataa = malloc(sizeof(t_dataa) * data->philonbr);

	// ft_printf("number of philos : %d\n", data->philonbr);
	// ft_printf("time to die : %d\n", data->timetodie);
	// ft_printf("time to eat : %d\n", data->timetoeat);
	// ft_printf("time to sleep : %d\n", data->timetosleep);
	// if (argc == 6)
	// 	ft_printf("nbr of time philo must eat : %d\n", data->philomusteat);

	
	data->i = 10;
	data->num = 0;
	data->index = 0;

	dataa->nb = 10;
	dataa->b = 0;
	//data->tabid = malloc(sizeof(pthread_t) * data->philonbr);
	dataa->mutex = malloc(sizeof(pthread_mutex_t) * data->philonbr);

	//ft_printf("%d\n", data->philonbr);


	int i = 0;
	while (i < data->philonbr)
	{
		pthread_mutex_init(&dataa->mutex[i], NULL);
		i++;
	}
	ft_thread_create(&dataa, &data);

	ft_printf("%d\n", dataa->nb);
	
	while (i > 0)
	{
		pthread_mutex_destroy(&dataa->mutex[i]);
		i--;
	}
	return (0);
}
