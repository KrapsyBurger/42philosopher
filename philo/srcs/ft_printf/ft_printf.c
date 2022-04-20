/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:39:36 by nfascia           #+#    #+#             */
/*   Updated: 2022/03/16 17:26:02 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_final_display(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, const char *)));
	else if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(args, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF"));
	else if (c == 'p')
		return (ft_put_pointer(va_arg(args, void *), "0123456789abcdef"));
	return (ft_putchar(c));
}

int	ft_printf(const char *s, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s)
		return (0);
	j = ft_strlen(s);
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			j--;
			j += ft_final_display(s[++i], args) - 1;
		}
		else
			ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (j);
}
