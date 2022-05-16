/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/16 20:10:19 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	routine_loop(t_thread *thread)
{
	is_someone_dead(thread);
	philo_eat(thread);
	is_someone_dead(thread);
	if (thread->philo->argc == 6)
	{
		if (thread->eat_count >= thread->philo->philomusteat)
		{
			thread->is_alive = 0;
			return (1);
		}
	}
	philo_sleep(thread);
	is_someone_dead(thread);
	philo_print(thread, thread->philo_idx, 4);
	is_someone_dead(thread);
	return (0);
}

void	*routine(void *s)
{
	t_thread	*thread;

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
		if (routine_loop(thread) == 1)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_thread	*thread;
	int			i;

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
