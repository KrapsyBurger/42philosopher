/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/09 16:01:29 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_test(void *s)
{
	t_thread *thread;
	thread = (t_thread *)s;
	int i;
	i = 0;
	int l;
	//ft_printf("ceci est le thread no : %d\n", threada[i].i);
	pthread_mutex_lock(&thread->mutex[i]);
	//ft_printf("incrementing the variable\n");
	ft_printf("ceci est le thread no : %d\n", thread[thread->b].i);
	thread->nb++;
	l = i;
	thread->b++;
	pthread_mutex_unlock(&thread->mutex[l]);
	return (NULL);
}

int	ft_thread_create(t_thread **thread, t_philo **philo)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (i < (*philo)->philonbr)
	{
		pthread_create(&(*thread)[i].id, NULL, ft_test, (*thread));
		(*thread)[i].i = a;
		//ft_printf("ceci est a : %d\n", (*threada)[i].i);
		i++; 
		a++;
		//ft_printf("ceci est a : %d\n", (*threada)[i].i);
	}
	i--;
	while (i >= 0)
	{
		pthread_join((*thread)[i].id, NULL);
		i--;
	}
	return (0);
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
	return (1);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_thread *thread;

	(void)argc;
	(void)argv;
	if (init_struct(&philo, &thread, argc, argv) == 0)
		return (free(philo), 0);

	//thread = malloc(sizeof(t_thread) * philo->philonbr);


	thread->nb = 10;
	thread->b = 0;


	int i = 0;
	while (i < philo->philonbr)
	{
		pthread_mutex_init(&thread->mutex[i], NULL);
		i++;
	}
	ft_thread_create(&thread, &philo);

	ft_printf("%d\n", thread->nb);
	
	while (i > 0)
	{
		pthread_mutex_destroy(&thread->mutex[i]);
		i--;
	}
	return (0);
}
