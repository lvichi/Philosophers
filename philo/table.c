/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:11:24 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/21 19:20:10 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo			*create_table(char **argv);
static t_philo	*create_philosophers(char **argv, int id);
void			print_table(t_philo *philo);
void			free_table(t_philo *philo);

t_philo	*create_table(char **argv)
{
	int		count;
	int		id;
	t_philo	*philo;
	t_philo	*temp_philo;
	t_philo	*first;

	id = 0;
	first = create_philosophers(argv, id++);
	if (!first)
		return (NULL);
	philo = first;
	count = ft_atoi(argv[0]);
	while (--count)
	{
		temp_philo = philo;
		philo = create_philosophers(argv, id++);
		philo->prev = temp_philo;
		philo->next = temp_philo->next;
		temp_philo->next = philo;
		(philo->next)->prev = philo;
	}
	return (first);
}

static t_philo	*create_philosophers(char **argv, int id)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->die = ft_atoi(argv[1]);
	philo->eat = ft_atoi(argv[2]);
	philo->sleep = ft_atoi(argv[3]);
	philo->meals = 0;
	philo->fork = 1;
	philo->thread = 0;
	philo->prev = philo;
	philo->next = philo;
	return (philo);
}

void	print_table(t_philo *philo)
{
	while (1)
	{
		write(1, "Philosopher ", 12);
		ft_putnbr(philo->id);
		write(1, ":\n", 2);
		write(1, "Die: ", 5);
		ft_putnbr(philo->die);
		write(1, " Eat: ", 6);
		ft_putnbr(philo->eat);
		write(1, " Sleep: ", 8);
		ft_putnbr(philo->sleep);
		write(1, " Meals: ", 8);
		ft_putnbr(philo->meals);
		write(1, " Fork: ", 7);
		ft_putnbr(philo->fork);
		write(1, "\n", 1);
		if ((philo->next)->id == 0)
			break ;
		philo = philo->next;
	}
}

void	free_table(t_philo *philo)
{
	t_philo	*temp_philo;
	t_philo	*first;

	temp_philo = philo;
	first = philo;
	while (temp_philo)
	{
		if (philo->next != first)
			temp_philo = philo->next;
		else 
			temp_philo = NULL;
		free(philo);
		philo = temp_philo;
	}
}
