/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/10 19:14:37 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *s)
{
	t_thread *thread; 
	thread = (t_thread *)s;
	if (thread->philo->philonbr % 2 == 0)
	{
		while (thread->thread_idx < thread->philo->philonbr)
		{
			if (pthread_mutex_lock(&thread->mutex[thread->mutex_idx]) == 0)
			if (pthread_mutex_lock(&thread->mutex[thread->philo->philonbr]) == 0)
				philo_print(&thread, &thread->philo, thread[thread->thread_idx].i, 2);
			pthread_mutex_lock(thread->mutex_print);
			thread->thread_idx += 2;
			pthread_mutex_unlock(thread->mutex_print);
			pthread_mutex_unlock(&thread->mutex[thread->mutex_idx]);
			pthread_mutex_unlock(&thread->mutex[thread->mutex_idx - 1]);
			
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_thread *thread;
	if (init_struct(&philo, &thread, argc, argv) == 0)
		return (free(philo), 0);
	thread->i = 0;
	ft_thread_create(&thread, &philo);
	destroy_mutex(&thread, &philo);
	return (0);
}
