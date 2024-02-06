/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:22 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/04 18:51:30 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long		ft_time(int start);
long		ft_atoi(char *nptr);
void		print_log(const char *format, int time, int id);
static int	ft_putnbr(long nbr);

long	ft_time(int start)
{
	struct timeval	current_time;
	int				now;

	gettimeofday(&current_time, NULL);
	now = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (now - start);
}

long	ft_atoi(char *nptr)
{
	size_t	n;
	int		i;
	int		negative;

	n = 0;
	i = 0;
	negative = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative = -1;
		i++;
	}
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			n = (n * 10) + (nptr[i] - 48);
		else
			break ;
		i++;
	}
	return (n * negative);
}

void	print_log(const char *format, int time, int id)
{
	int		i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] == 'd' && ++i)
		{
			ft_putnbr(time);
			write(1, "\t", 1);
		}
		else if (format[i] == '%' && format[i + 1] == 'i' && ++i)
			ft_putnbr(id);
		else
			write(1, &format[i], 1);
	}
}

static int	ft_putnbr(long nbr)
{
	char	c;
	int		size;

	size = 0;
	if (nbr < 0)
	{
		size += write(1, "-", 1);
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		size += ft_putnbr(nbr / 10);
		nbr = nbr % 10;
	}
	c = nbr + '0';
	size += write(1, &c, 1);
	return (size);
}
