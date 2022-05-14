/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/14 17:18:17 by nfascia          ###   ########.fr       */
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
	
	philo_print(&thread->philo, thread->philo_idx, 2);
	
	usleep(thread->philo->timetoeat * 1000);
	
	thread->is_eating = 1;
	thread->is_sleeping = 0;
	thread->is_thinking = 1;
	thread->eat_count++;
	thread->last_meal = current_time() - thread->philo->start_time;


	pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx - 1]);
	pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);

	if (thread->philo_idx == 0)
	{
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx]);
		pthread_mutex_unlock(&thread->philo->mutex_fork[thread->philo_idx + 1]);
	}
	return (0);
}


int	ft_filling_pair(t_thread **thread)
{
	int	i;

	i = 0;
	while (thread[i])
	{
		if ((*thread)[i].philo_idx % 2 != 0)
		{
			(*thread)[i].is_eating = 1;
		}
		i++;
	}
	return (0);
}

void	*routine(void *s)
{
	t_thread *thread; 
	thread = (t_thread *)s;

	if (thread->philo->philonbr % 2 == 0)
		ft_filling_pair(&thread);
	

	while (thread->is_alive == 1)
	{
		if (thread->is_eating == 0)
		{
			philo_eat(thread);
		}
		else if (thread->is_thinking == 0)
		{
			philo_print(&thread->philo, thread->philo_idx, 4);
			thread->is_thinking = 1;
			thread->is_eating = 0;
			thread->is_sleeping = 1;
		}
		else if (thread->is_sleeping == 0)
		{
			thread->is_thinking = 0;
			thread->is_eating = 1;
			thread->is_sleeping = 1;
			philo_print(&thread->philo, thread->philo_idx, 3);
			usleep(thread->philo->timetosleep * 1000);
		}
		if (thread->philo->argc == 6)
		{
			if (thread->eat_count >= thread->philo->philomusteat)
			{
				philo_print(&thread->philo, thread->philo_idx, 5);
				thread->is_alive = 0;
				break ; 
			}
		}
		if (thread->last_meal >= thread->philo->timetodie * 1000)
		{
			philo_print(&thread->philo, thread->philo_idx, 5);
			thread->is_alive = 0;
			break ;
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
