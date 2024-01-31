/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:11:24 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 00:15:42 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				create_table(t_table **table, char **argv);
static int		create_philosophers(t_table **table, char **argv, int count);
static t_philo	*create_philo(char **argv, int id);
void			free_table(t_table *table);
int				ft_time(int start);

int	create_table(t_table **table, char **argv)
{
	*table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!table)
		return (1);
	(*table)->start_time = ft_time(0);
	(*table)->die_time = ft_atoi(argv[1]);
	(*table)->meals_limit = -1;
	if (argv[4])
		(*table)->meals_limit = ft_atoi(argv[4]);
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
	philo->fork = 1;
	philo->alive = 1;
	philo->got_fork = 0;
	philo->sleep = 0;
	philo->thinking = 0;
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

int	ft_time(int start)
{
	struct timeval	current_time;
	int				now;

	gettimeofday(&current_time, NULL);
	now = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) %
		((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) / 100000);
	return (now - start);
}