/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:53:25 by nfascia           #+#    #+#             */
/*   Updated: 2022/03/16 20:55:15 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

unsigned int	ft_putchar(char c);
unsigned int	ft_putstr(const char *s);
unsigned int	ft_putnbr(int nb);
unsigned int	ft_display(char c, va_list args);
int				ft_printf(const char *s, ...);
unsigned int	ft_putunsigned(unsigned int nb);
unsigned int	ft_putnbr_base(unsigned int nbr, char *base);
unsigned int	ft_put_pointer(void *a, char *base);
unsigned int	ft_final_display(char c, va_list args);
unsigned int	ft_strlen(const char *s);

#endif