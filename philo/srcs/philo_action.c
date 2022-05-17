/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:05:44 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/17 17:37:27 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	fork_lock_1st_philo(t_thread *thread)
{
	if (pthread_mutex_lock(&thread->philo->mutex_fork
			[thread->philo->philonbr - 1]) == 0)
	{
		philo_print(thread, thread->philo_idx, 1);
		is_someone_dead(thread);
	}
	if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx]) == 0)
	{
		philo_print(thread, thread->philo_idx, 1);
		is_someone_dead(thread);
	}
}

void	fork_lock(t_thread *thread)
{
	if (thread->philo_idx == 0)
		fork_lock_1st_philo(thread);
	else
	{
		if (pthread_mutex_lock(&thread->philo->mutex_fork
				[thread->philo_idx - 1]) == 0)
		{
			philo_print(thread, thread->philo_idx, 1);
			is_someone_dead(thread);
		}
		if (pthread_mutex_lock(&thread->philo->mutex_fork
				[thread->philo_idx]) == 0)
		{
			philo_print(thread, thread->philo_idx, 1);
			is_someone_dead(thread);
		}	
	}
}

int	philo_eat(t_thread *thread)
{
	fork_lock(thread);
	philo_print(thread, thread->philo_idx, 2);
	pthread_mutex_lock(thread->philo->mutex_rip);
	thread->last_meal = current_time() - thread->philo->start_time;
	pthread_mutex_unlock(thread->philo->mutex_rip);
	thread->eat_count++;
	ft_usleep(thread, thread->philo->timetoeat);
	if (thread->philo_idx == 0)
	{
		pthread_mutex_unlock(&thread->philo->mutex_fork
		[thread->philo->philonbr - 1]);
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);
	}
	else
	{
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx - 1]);
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);
	}
	return (0);
}

void	philo_sleep(t_thread *thread)
{
	philo_print(thread, thread->philo_idx, 3);
	ft_usleep(thread, thread->philo->timetosleep);
}
