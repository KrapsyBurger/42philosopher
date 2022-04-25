#include "philo.h"
#include "ft_printf.h"
#include "pthread.h"


void	*ft_test(void *s)
{
	t_data *data;

	data = (t_data *)s;
	pthread_mutex_lock(&lock);
	data->i++;
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int main()
{
	t_data *data;
	data = malloc(sizeof(t_data));
	data->i = 10;

	pthread_t id1;
	pthread_t id2;
	pthread_t id3;


	pthread_mutex_init(&lock, NULL);
	usleep(2000);
	pthread_create(&id1, NULL, ft_test, data);
	pthread_create(&id2, NULL, ft_test, data);
	pthread_create(&id3, NULL, ft_test, data);
	
	//pthread_mutex_lock(&lock);
	ft_printf("%d\n", data->i);
	//pthread_mutex_unlock(&lock);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);

	pthread_mutex_destroy(&lock);
	return (0);
}