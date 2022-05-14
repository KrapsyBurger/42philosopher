/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:32:50 by nfascia           #+#    #+#             */
/*   Updated: 2022/05/14 19:33:16 by nfascia          ###   ########.fr       */
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
	else if (nptr[i] == '-')
	{
		i++;
		neg *= -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result *= neg);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

char	*ft_action(int action)
{
	if (action == 1)
		return ("has taken a fork\n");
	else if (action == 2)
		return ("is eating\n");
	else if (action == 3)
		return ("is sleeping\n");
	else if (action == 4)
		return ("is thinking\n");
	else if (action == 5)
		return ("died\n");
	return (NULL);
}

int	philo_print(t_philo **philo, int i, int action)
{
	pthread_mutex_lock((*philo)->mutex_print);
	printf("%lld %d %s", current_time() - (*philo)->start_time,
		i + 1, ft_action(action));
	pthread_mutex_unlock((*philo)->mutex_print);
	return (0);
}
