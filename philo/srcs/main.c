#include "philo.h"

void	*ft_test(void *s)
{
	t_data *data;
	data = (t_data *)s;
	int i;
	i = 0;
	int l;
	//ft_printf("ceci est le thread no : %d\n", dataa[i].i);
	pthread_mutex_lock(&data->mutex[i]);
	//ft_printf("incrementing the variable\n");
	ft_printf("ceci est le thread no : %d\n", data[data->b].i);
	data->nb++;
	l = i;
	data->b++;
	pthread_mutex_unlock(&data->mutex[l]);
	return (NULL);
}

int	ft_thread_create(t_data **data, t_philoinfo **philoinfo)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (i < (*philoinfo)->philonbr)
	{
		pthread_create(&(*data)[i].id, NULL, ft_test, (*data));
		(*data)[i].i = a;
		//ft_printf("ceci est a : %d\n", (*dataa)[i].i);
		i++; 
		a++;
		//ft_printf("ceci est a : %d\n", (*dataa)[i].i);
	}
	i--;
	while (i >= 0)
	{
		pthread_join((*data)[i].id, NULL);
		i--;
	}
	return (0);
}


int	ft_init(t_philoinfo **philoinfo, int argc, char **argv)
{
	(*philoinfo) = malloc(sizeof(t_philoinfo));

	if (argc > 6 || argc < 5)
		return (0);

	(*philoinfo)->philonbr = ft_atoi(argv[1]);
	(*philoinfo)->timetodie = ft_atoi(argv[2]);
	(*philoinfo)->timetoeat = ft_atoi(argv[3]);
	(*philoinfo)->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*philoinfo)->philomusteat = ft_atoi(argv[5]);
	return (1);
}

int main(int argc, char **argv)
{
	t_philoinfo *philoinfo;
	t_data *data;

	(void)argc;
	(void)argv;
	philoinfo = malloc(sizeof(t_philoinfo));
	if (ft_init(&philoinfo, argc, argv) == 0)
		return (free(philoinfo), 0);

	data = malloc(sizeof(t_data) * philoinfo->philonbr);


	data->nb = 10;
	data->b = 0;
	data->mutex = malloc(sizeof(pthread_mutex_t) * philoinfo->philonbr);


	int i = 0;
	while (i < philoinfo->philonbr)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	ft_thread_create(&data, &philoinfo);

	ft_printf("%d\n", data->nb);
	
	while (i > 0)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i--;
	}
	return (0);
}
