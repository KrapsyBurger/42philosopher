/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:32:50 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/18 18:08:25 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned int	ft_strlen(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	string_check(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		neg;

	i = 0;
	result = 0;
	neg = 1;
	if (nptr == NULL || ft_strlen((char *)nptr) > 12)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' )
		i++;
	else if (nptr[i] == '-' || string_check(nptr) == 1)
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result *= neg);
}

char	*ft_action(int action)
{
	if (action == 1)
		return ("\033[94mhas taken a fork\n\033[0m");
	else if (action == 2)
		return ("\e[38;5;118mis eating\n\033[0m");
	else if (action == 3)
		return ("\033[33mis sleeping\n\033[0m");
	else if (action == 4)
		return ("\033[95mis thinking\n\033[0m");
	else if (action == 5)
		return ("\e[38;5;196mdied\n\033[0m");
	return (NULL);
}

int	philo_print(t_thread *thread, int i, int action)
{
	pthread_mutex_lock(thread->philo->mutex_death);
	if (thread->philo->is_someone_dead == 1)
	{
		pthread_mutex_unlock(thread->philo->mutex_death);
		return (0);
	}
	if (thread->is_alive == 1)
	{
		pthread_mutex_lock(thread->philo->mutex_print);
		printf("%lld %d %s", current_time() - thread->philo->start_time,
			i + 1, ft_action(action));
		pthread_mutex_unlock(thread->philo->mutex_print);
	}
	pthread_mutex_unlock(thread->philo->mutex_death);
	return (0);
}
