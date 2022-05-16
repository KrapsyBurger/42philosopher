/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:34:09 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/16 18:13:19 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				argc;
	int				timetoeat;
	int				timetodie;
	int				timetosleep;
	int				philonbr;
	int				philomusteat;
	long long		start_time;
	int				is_someone_dead;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_print;
	struct	s_dataa **thread;
}	t_philo;

typedef struct s_dataa
{
	int			philo_idx;
	int			is_alive;
	int			eat_count;
	long long	last_meal;
	pthread_t	id;
	t_philo		*philo;
}	t_thread;

// utils
long		ft_atoi(const char *nptr);
long long	current_time(void);
int			is_someone_dead(t_thread *thread);

// init and destroy
int			init_struct(t_philo **philo, t_thread **thread,
				int argc, char **argv);
int			init_mutex(t_philo **philo);
int			destroy_mutex(t_philo **philo);
int			ft_thread_create(t_thread **thread, t_philo **philo);

// routine and action
void		*routine(void *s);
char		*ft_action(int action);
int			philo_print(t_philo **philo, int i, int action);

#endif
