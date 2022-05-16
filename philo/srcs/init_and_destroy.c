/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:55:13 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/16 20:16:53 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	destroy_mutex(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->philonbr)
	{
		if (pthread_mutex_destroy(&(*philo)->mutex_fork[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_destroy((*philo)->mutex_print) != 0)
		return (0);
	if (pthread_mutex_destroy((*philo)->mutex_death) != 0)
		return (0);
	if (pthread_mutex_destroy((*philo)->mutex_rip) != 0)
		return (0);
	return (1);
}

int	init_mutex(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->philonbr)
	{
		if (pthread_mutex_init(&(*philo)->mutex_fork[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init((*philo)->mutex_print, NULL) != 0)
		return (0);
	if (pthread_mutex_init((*philo)->mutex_death, NULL) != 0)
		return (0);
	if (pthread_mutex_init((*philo)->mutex_rip, NULL) != 0)
		return (0);
	return (1);
}

int	init_philo(t_philo **philo, char **argv, int argc)
{
	(*philo)->is_someone_dead = 0;
	(*philo)->argc = argc;
	(*philo)->start_time = current_time();
	(*philo)->philonbr = ft_atoi(argv[1]);
	if ((*philo)->philonbr == 0)
		return (1);
	(*philo)->timetodie = ft_atoi(argv[2]);
	(*philo)->timetoeat = ft_atoi(argv[3]);
	(*philo)->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*philo)->philomusteat = ft_atoi(argv[5]);
	return (0);
}

int	init_struct(t_philo **philo, t_thread **thread, int argc, char **argv)
{
	(*philo) = malloc(sizeof(t_philo));
	if ((*philo) == NULL)
		return (0);
	if (argc > 6 || argc < 5)
		return (0);
	if (init_philo(philo, argv, argc) == 1)
		return (0);
	(*thread) = malloc(sizeof(t_thread) * (*philo)->philonbr);
	if ((*thread) == NULL)
		return (0);
	(*philo)->mutex_fork = malloc(sizeof(pthread_mutex_t) * (*philo)->philonbr);
	(*philo)->mutex_print = malloc(sizeof(pthread_mutex_t));
	(*philo)->mutex_death = malloc(sizeof(pthread_mutex_t));
	(*philo)->mutex_rip = malloc(sizeof(pthread_mutex_t));
	if (!(*philo)->mutex_fork || !(*philo)->mutex_print
		|| !(*philo)->mutex_rip || !(*philo)->mutex_death)
		return (0);
	if (init_mutex(philo) == 0)
		return (0);
	return (1);
}

int	ft_thread_create(t_thread **thread, t_philo **philo)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (i < (*philo)->philonbr)
	{
		(*thread)[i].philo_idx = a;
		(*thread)[i].is_alive = 1;
		(*thread)[i].last_meal = 0;
		if ((*philo)->argc == 6)
			(*thread)[i].eat_count = 0;
		(*thread)[i].philo = (*philo);
		pthread_create(&(*thread)[i].id, NULL, routine, &(*thread)[i]);
		i++;
		a++;
	}
	philo_death_check(thread, philo);
	return (0);
}
