/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:35:10 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/30 22:29:24 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_print_s(char *arg)
{
	if (arg)
		return (write(1, arg, str_len(arg)));
	return (0);
}

static int	ft_check_format(char *format, va_list ap)
{
	if (*format == 's')
		return (ft_print_s(va_arg(ap, char *)));
	if (*format == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		size;
	va_list	ap;

	i = 0;
	size = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && ++i)
			size += ft_check_format(&((char *)format)[i++], ap);
		else
		{
			size++;
			write(1, &format[i++], 1);
		}
	}
	va_end(ap);
	return (size);
}
