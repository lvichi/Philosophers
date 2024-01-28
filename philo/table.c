/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:11:24 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/28 20:44:46 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				create_table(t_table **table, char **argv);
static int		create_philosophers(t_table **table, char **argv, int count);
static t_philo	*create_philo(char **argv, int id);
void			free_table(t_table *table);
void			print_table(t_table *table);

int	create_table(t_table **table, char **argv)
{
	*table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!table)
		return (1);
	(*table)->die_time = ft_atoi(argv[1]);
	(*table)->meals_limit = -1;
	if (argv[4])
		(*table)->meals_limit = ft_atoi(argv[4]);
	//(*table)->print = 0;
	if (create_philosophers(table, argv, ft_atoi(argv[0])))
	{
		free_table(*table);
		return (1);
	}
	return (0);
}

static int	create_philosophers(t_table **table, char **argv, int count)
{
	t_philo	*temp_philo;
	t_philo	*first;
	t_philo	*philos;
	int		id;

	id = 0;
	first = create_philo(argv, id++);
	if (!first)
		return (1);
	philos = first;
	while (--count)
	{
		temp_philo = philos;
		philos = create_philo(argv, id++);
		if (!philos)
		{
			(*table)->philos = first;
			return (1);
		}
		philos->next = temp_philo->next;
		temp_philo->next = philos;
	}
	(*table)->philos = first;
	return (0);
}

static t_philo	*create_philo(char **argv, int id)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->eat_time = ft_atoi(argv[1]);
	philo->sleep_time = ft_atoi(argv[2]);
	philo->meals_count = 0;
	//philo->fork = 0;
	philo->thread = 0;
	philo->next = philo;
	return (philo);
}

void	free_table(t_table *table)
{
	t_philo	*temp_philo;
	t_philo	*first;

	temp_philo = table->philos;
	first = table->philos;
	while (temp_philo)
	{
		if (table->philos->next != first)
			temp_philo = table->philos->next;
		else
			temp_philo = NULL;
		free(table->philos);
		table->philos = temp_philo;
	}
	free(table);
}

void	print_table(t_table *table)
{
	while (1)
	{
		write(1, "Philosopher ", 12);
		ft_putnbr(table->philos->id);
		write(1, ":\n", 2);
		write(1, "Die: ", 5);
		ft_putnbr(table->die_time);
		write(1, " Eat: ", 6);
		ft_putnbr(table->philos->eat_time);
		write(1, " Sleep: ", 8);
		ft_putnbr(table->philos->sleep_time);
		write(1, " Meals: ", 8);
		ft_putnbr(table->philos->meals_count);
		write(1, " Meals_limit: ", 14);
		ft_putnbr(table->meals_limit);
		// write(1, " Fork: ", 7);
		// ft_putnbr(table->philos->fork);
		write(1, "\n", 1);
		if ((table->philos->next)->id == 0)
			break ;
		table->philos = table->philos->next;
	}
}
