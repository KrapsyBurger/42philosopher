/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:37:30 by nfascia           #+#    #+#             */
/*   Updated: 2022/04/08 17:15:50 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned int	ft_putstr(const char *s)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	if (s[0] == '\0')
	{
		return (0);
	}
	return (ft_strlen(s));
}

unsigned int	ft_putnbr(int nb)
{
	long			a;
	long			nb2;
	unsigned int	j;

	a = 1;
	nb2 = nb;
	j = 0;
	if (nb == 0)
		j += ft_putchar('0');
	if (nb2 < 0)
	{
		ft_putchar('-');
		nb2 = -nb2;
		j++;
	}
	while (nb2 / a > 0)
		a *= 10;
	while (a > 1)
	{
		j++;
		a /= 10;
		ft_putchar((nb2 / a) % 10 + '0');
	}
	return (j);
}
