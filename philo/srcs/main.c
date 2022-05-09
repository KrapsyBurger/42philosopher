/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/09 18:23:56 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *s)
{
	t_thread *thread;
	thread = (t_thread *)s;
	int i;
	i = 0;
	int l;
	pthread_mutex_lock(&thread->mutex[i]);
	ft_printf("ceci est le thread no : %d\n", thread[thread->b].i);
	thread->nb++;
	l = i;
	thread->b++;
	pthread_mutex_unlock(&thread->mutex[l]);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_thread *thread;

	(void)argc;
	(void)argv;
	if (init_struct(&philo, &thread, argc, argv) == 0)
		return (free(philo), 0);

	thread->nb = 10;
	thread->b = 0;
	ft_thread_create(&thread, &philo);

	ft_printf("%d\n", thread->nb);
	
	int i = philo->philonbr;
	while (i > 0)
	{
		pthread_mutex_destroy(&thread->mutex[i]);
		i--;
	}
	return (0);
}
