#include "philo.h"
#include "ft_printf.h"
#include "pthread.h"


void	*ft_test(void *s)
{
	t_data *data;

	data = (t_data *)s;

	pthread_mutex_lock(&data->lock[data->num]);
	data->i++;
	pthread_mutex_unlock(&data->lock[data->num]);
	
	return (NULL);
}

int main()
{
	t_data *data;
	data = malloc(sizeof(t_data));
	data->i = 10;
	data->num = 0;

	pthread_t *tabid;
	tabid = malloc(sizeof(pthread_t) * 3);
//	pthread_t id2;
//	pthread_t id3;
	data->lock = malloc(sizeof(pthread_mutex_t) * 3);


	//pthread_mutex_init(&data->lock[0], NULL);

	pthread_mutex_init(&data->lock[0], NULL);
	pthread_mutex_init(&data->lock[1], NULL);
	pthread_mutex_init(&data->lock[2], NULL);

	pthread_create(&tabid[0], NULL, ft_test, data);
	pthread_create(&tabid[1], NULL, ft_test, data);
	pthread_create(&tabid[2], NULL, ft_test, data);

	ft_printf("%d\n", data->i);

	pthread_join(tabid[0], NULL);
	pthread_join(tabid[1], NULL);
	pthread_join(tabid[2], NULL);


	pthread_mutex_init(&data->lock[0], NULL);
	pthread_mutex_init(&data->lock[1], NULL);
	pthread_mutex_init(&data->lock[2], NULL);
	
	// pthread_mutex_destroy(&data->lock);
	return (0);
}
