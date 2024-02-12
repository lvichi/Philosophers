/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:22 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/12 21:45:11 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(int start);
long	ft_atoi(char *nptr);
void	print_log(t_table *table, int type);
int		ft_putnbr(long nbr);
char	*sem_format_name(int id);

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

void	print_log(t_table *table, int type)
{
	sem_wait((table->philo).sem_philo);
	if (!(table->philo).alive)
		type = 0;
	sem_post((table->philo).sem_philo);
	if (type > 0)
	{
		sem_wait(table->sem_print);
		ft_putnbr(ft_time(table->start_time));
		write(1, "\t", 1);
		ft_putnbr((table->philo).id);
		if (type == 1)
			write (1, " has taken a fork\n", 18);
		else if (type == 2)
			write (1, " is eating\n", 11);
		else if (type == 3)
			write (1, " is sleeping\n", 13);
		else if (type == 4)
			write (1, " is thinking\n", 13);
		else if (type == 5)
			write (1, " died\n", 6);
		sem_post(table->sem_print);
	}
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

char	*sem_format_name(int id)
{
	char *name;

	name = (char *)malloc(sizeof(char) * 10);
	if (!name)
		return (NULL);
	name[0] = '/';
	name[1] = 'p';
	name[2] = 'h';
	name[3] = 'i';
	name[4] = 'l';
	name[5] = 'o';
	name[8] = ((id % 10) + '0');
	id /= 10;
	if (id)
		name[7] = ((id % 10) + '0');
	else
		name[7] = '0';
	id /= 10;
	if (id)
		name[6] = ((id % 10) + '0');
	else
		name[6] = '0';
	name[9] = 0;
	return (name);
}