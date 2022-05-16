/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:31:26 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/16 20:15:35 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_someone_dead(t_thread *thread)
{
	if (current_time() - thread->philo->start_time
		- thread->last_meal >= thread->philo->timetodie)
	{	
		philo_print(thread, thread->philo_idx, 5);
		pthread_mutex_lock(thread->philo->mutex_death);
		thread->is_alive = 0;
		thread->philo->is_someone_dead = 1;
		pthread_mutex_unlock(thread->philo->mutex_death);
		return (1);
	}
	return (0);
}

int	ft_usleep(t_thread *thread, long long time_in_ms)
{
	long long	start_time;

	start_time = 0;
	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms
		&& is_someone_dead(thread) == 0)
		usleep(50);
	return (0);
}

void	ft_free(t_thread **thread, t_philo **philo)
{
	free((*philo)->mutex_fork);
	free((*thread));
	free((*philo)->mutex_death);
	free((*philo)->mutex_print);
	free((*philo)->mutex_rip);
	free((*philo));
}

int	philo_death_check(t_thread **thread, t_philo **philo)
{
	int	a;

	a = 0;
	if ((*philo)->argc == 5)
	{
		while ((*philo)->is_someone_dead == 0)
		{
			a = 0;
			while (a < (*philo)->philonbr)
			{
				pthread_mutex_lock((*philo)->mutex_rip);
				if (is_someone_dead(thread[a]) == 1)
				{
					pthread_mutex_unlock((*philo)->mutex_rip);
					philo_print(thread[a], thread[a]->philo_idx, 5);
					return (1);
				}
				pthread_mutex_unlock((*philo)->mutex_rip);
			}
		}
		is_someone_dead((*thread));
	}
	return (0);
}
