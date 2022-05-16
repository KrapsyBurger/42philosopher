/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/16 19:31:48 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_eat(t_thread *thread)
{
	if (thread->philo_idx == 0)
	{
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo->philonbr - 1]) == 0)
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
	else 
	{
		if (pthread_mutex_lock(&thread->philo->mutex_fork[thread->philo_idx - 1]) == 0)
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

	philo_print(thread, thread->philo_idx, 2);
	pthread_mutex_lock(thread->philo->mutex_rip);
	thread->last_meal = current_time() - thread->philo->start_time;
	pthread_mutex_unlock(thread->philo->mutex_rip);
	thread->eat_count++;

	ft_usleep(thread, thread->philo->timetoeat);


	if (thread->philo_idx == 0)
	{
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo->philonbr - 1]);
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

void	*routine(void *s)
{
	t_thread *thread;
	thread = (t_thread *)s;

	if (thread->philo->philonbr % 2 == 0)
	{
		if (thread->philo_idx % 2 != 0)
			ft_usleep(thread, thread->philo->timetoeat / 2);
	}
	else if (thread->philo->philonbr % 2 != 0)
	{
		if (thread->philo_idx % 2 == 0)
			ft_usleep(thread, thread->philo->timetoeat / 2);
	}
	while (thread->is_alive == 1 && is_someone_dead(thread) == 0)
	{
		is_someone_dead(thread);
		philo_eat(thread);
		is_someone_dead(thread);
		if (thread->philo->argc == 6)
		{
			if (thread->eat_count >= thread->philo->philomusteat)
			{
				thread->is_alive = 0;
				break ;
			}
		}
		philo_sleep(thread);
		is_someone_dead(thread);
		philo_print(thread, thread->philo_idx, 4);
		is_someone_dead(thread);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_thread *thread;
	int		i;

	i = 0;
	if (init_struct(&philo, &thread, argc, argv) == 0)
		return (free(philo), 0);
	ft_thread_create(&thread, &philo);
	destroy_mutex(&philo);
	while (i < philo->philonbr)
	{
		pthread_join(thread[i].id, NULL);
		i++;
	}
	ft_free(&thread, &philo);
	return (0);
}
