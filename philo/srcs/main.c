/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/10 18:02:07 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *s)
{
	t_thread *thread; 
	thread = (t_thread *)s;
	int i;
	i = 0;
	while (i < thread->philo->philonbr)
	{
		
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_thread *thread;

	if (init_struct(&philo, &thread, argc, argv) == 0)
		return (free(philo), 0);

	thread->philo = philo;
	thread->tabidx = 0;
	ft_thread_create(&thread, &philo);
	destroy_mutex(&thread, &philo);
	return (0);
}
