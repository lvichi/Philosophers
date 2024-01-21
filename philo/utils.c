/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:22 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/21 18:06:50 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size);
size_t	array_len(char **array);
size_t	str_len(char *str);
long	ft_atoi(char *nptr);
void	ft_putnbr(long nbr);

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

size_t	array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	ft_putnbr(long nbr)
{
	char	c;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		nbr = nbr % 10;
	}
	c = nbr + '0';
	write(1, &c, 1);
}
