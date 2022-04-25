/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:47:57 by nfascia           #+#    #+#             */
/*   Updated: 2022/04/20 16:59:29 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	base_len;
	unsigned int	denom;
	long			nbr2;
	unsigned int	j;

	base_len = ft_strlen(base);
	denom = 1;
	nbr2 = nbr;
	j = 0;
	if (nbr2 < 0)
	{
		return (0);
	}
	while (nbr2 / denom / base_len > 0)
	{
		denom *= base_len;
	}
	while (denom > 0)
	{
		j++;
		ft_putchar(base[nbr2 / denom % base_len]);
		denom /= base_len;
	}
	return (j);
}

unsigned int	ft_put_pointer(void *a, char *base)
{
	unsigned int		base_len;
	unsigned long long	denom;
	void				*nbr2;
	unsigned int		j;

	base_len = ft_strlen(base);
	denom = 1;
	nbr2 = a;
	j = 0;
	ft_putstr("0x");
	if ((long long)nbr2 < 0)
	{
		return (0);
	}
	while ((unsigned long long)nbr2 / denom / base_len > 0)
	{
		denom *= base_len;
	}
	while (denom > 0)
	{
		j++;
		ft_putchar(base[(unsigned long long)nbr2 / denom % base_len]);
		denom /= base_len;
	}
	return (j + 2);
}

unsigned int	ft_putunsigned(unsigned int nb)
{
	unsigned long	a;
	unsigned long	nb2;
	unsigned int	j;

	a = 1;
	nb2 = nb;
	j = 0;
	if (nb2 == 0)
		return (ft_putchar('0'));
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
