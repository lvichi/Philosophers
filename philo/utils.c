/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:22 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 22:30:11 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_time(int start);
void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atoi(char *nptr);
int		ft_putnbr(long nbr);
void	print_log(const char *format, int time, int id);

int	ft_time(int start)
{
	struct timeval	current_time;
	int				now;

	gettimeofday(&current_time, NULL);
	now = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		% ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
			/ 1000000);
	return (now - start);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	size = nmemb * size;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	while (size)
		((char *)ret)[--size] = 0;
	return (ret);
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

int	ft_putnbr(long nbr)
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

void	print_log(const char *format, int time, int id)
{
	int		i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] == 'd' && ++i)
		{
			ft_putnbr(time);
			if (time <= 9999)
				write(1, " ms\t", 4);
			else
				write(1, " ms", 3);
		}
		else if (format[i] == '%' && format[i + 1] == 'i' && ++i)
			ft_putnbr(id);
		else
			write(1, &format[i], 1);
	}
}
