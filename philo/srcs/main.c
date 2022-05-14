/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/14 19:58:19 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_eat(t_thread *thread)
{ 
	if (thread->philo_idx == 0)
	{
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx]) == 0)
			philo_print(&thread->philo, thread->philo_idx, 1);
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx + 1]) == 0)
			philo_print(&thread->philo, thread->philo_idx, 1);
	}
	else 
	{
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx - 1]) == 0)
			philo_print(&thread->philo, thread->philo_idx, 1);
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx]) == 0)
			philo_print(&thread->philo, thread->philo_idx, 1);
	}
	// printf("\n\n%lld --------- %d\n\n", current_time() - thread->philo->start_time - thread->last_meal, thread->philo->timetodie); 

	philo_print(&thread->philo, thread->philo_idx, 2);
	thread->last_meal = current_time() - thread->philo->start_time;
	thread->eat_count++;

	usleep(thread->philo->timetoeat * 1000);


	pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx - 1]);
	pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);

	if (thread->philo_idx == 0)
	{
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx + 1]);
	}
	return (0);
}

void	philo_sleep(t_thread *thread)
{
	philo_print(&thread->philo, thread->philo_idx, 3);
	usleep(thread->philo->timetosleep * 1000);
	if (current_time() - thread->philo->start_time - thread->last_meal >= thread->philo->timetodie)
	{
		philo_print(&thread->philo, thread->philo_idx, 5);
		thread->is_alive = 0;
		exit (1) ;
	}
}

void	*routine(void *s)
{
	t_thread *thread; 
	thread = (t_thread *)s;

	if (thread->philo->philonbr % 2 == 0)
	{
		if (thread->philo_idx % 2 != 0)
			usleep(thread->philo->timetoeat * 1000);
	}
	else if (thread->philo->philonbr % 2 != 0)
	{
		if (thread->philo_idx % 2 == 0)
			usleep(thread->philo->timetoeat * 1000);
	}
	while (thread->is_alive == 1)
	{
		if (current_time() - thread->philo->start_time - thread->last_meal >= thread->philo->timetodie)
		{
			philo_print(&thread->philo, thread->philo_idx, 5);
			thread->is_alive = 0;
			break ;
		}
		philo_eat(thread);
		philo_print(&thread->philo, thread->philo_idx, 4);
		philo_sleep(thread);
		if (thread->philo->argc == 6)
		{
			if (thread->eat_count >= thread->philo->philomusteat)
			{
				philo_print(&thread->philo, thread->philo_idx, 5);
				thread->is_alive = 0;
				break ;
			}
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
	ft_thread_create(&thread, &philo);
	destroy_mutex(&philo);
	return (0);
}
