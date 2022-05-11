/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/11 19:03:10 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// int	is_dying_hungry(t_thread **thread)
// {
// 	int	i;

// 	i = 0;
// 	while (thread[i])
// 	{
// 		if ((*thread)[i].last_meal >= (*thread)->philo->timetodie)
// 		{
// 			printf("COUCOU");
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	philo_eat(t_thread **thread)
{
	if (pthread_mutex_lock(&(*thread)->philo->mutex_fork[(*thread)->philo_idx]) == 0)
	philo_print(&(*thread)->philo, (*thread)->philo_idx, 1);

	if (pthread_mutex_lock(&(*thread)->philo->mutex_fork[(*thread)->philo_idx + 1]) == 0)
	philo_print(&(*thread)->philo, (*thread)->philo_idx, 1);
		
	philo_print(&(*thread)->philo, (*thread)->philo_idx, 2);

	usleep((*thread)->philo->timetoeat);

	pthread_mutex_unlock(&(*thread)->philo->mutex_fork[(*thread)->philo_idx]);
	pthread_mutex_unlock(&(*thread)->philo->mutex_fork[(*thread)->philo_idx + 1]);

	(*thread)->last_meal = current_time() - (*thread)->philo->start_time;
	(*thread)->eat_count = 1;

	if ((*thread)->last_meal >= (*thread)->philo->timetodie)
	{
		(*thread)->is_alive = 0;
		philo_print(&(*thread)->philo, (*thread)->philo_idx, 5);
	}
	return (0);
}

void	philo_think(t_thread **thread)
{
		philo_print(&(*thread)->philo, (*thread)->philo_idx, 4);
}

void	philo_sleep(t_thread **thread)
{
		philo_print(&(*thread)->philo, (*thread)->philo_idx, 3);
		usleep((*thread)->philo->timetosleep);
}


void	*routine(void *s)
{
	t_thread *thread; 
	thread = (t_thread *)s;
	// (void)thread;
	while (thread->is_alive == 1)
	{
		if (thread->philo_idx % 2 == 0)
			philo_eat(&thread);
		else if (thread->eat_count == 1)
			philo_sleep(&thread);
		
			philo_think(&thread);
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
