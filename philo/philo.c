/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/09 17:09:49 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);
static void	start_brainstorm(t_table *table);
static void	check_alive(t_table *table, long now);
static void	end_brainstorm(t_table *table);

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
		write (2, "Wrong arguments, only numbers between 1 and INT_MAX\n", 52);
	else if (create_table(&table, &argv[1]))
		write (2, "Failed to create philosophers\n", 30);
	else if (init_threads(table))
		write (2, "Failed to create threads\n", 25);
	else
		start_brainstorm(table);
}

static int	check_input(char **argv)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9' || j > 10)
				return (1);
	}
	i = -1;
	while (argv[++i])
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) == 0)
			return (1);
	return (0);
}

static void	start_brainstorm(t_table *table)
{
	long	now;

	while (!table->end_flag)
	{
		now = ft_time(table->start_time);
		pthread_mutex_lock(&(table->philos->m_philo));
		if (table->philos->thinking && table->philos->thinking--)
			print_log("%d %i is thinking\n", now, table->philos->id);
		while (table->philos->got_fork && table->philos->got_fork--)
			print_log("%d %i has taken a fork\n", now, table->philos->id);
		if (table->philos->eating && table->philos->eating--)
			print_log("%d %i is eating\n", now, table->philos->id);
		if (table->philos->sleeping && table->philos->sleeping--)
			print_log("%d %i is sleeping\n", now, table->philos->id);
		table->total_meals[table->philos->id - 1] = table->philos->meals_count;
		pthread_mutex_unlock(&(table->philos->m_philo));
		table->philos = table->philos->next;
		check_alive(table, now);
	}
	end_brainstorm(table);
}

static void	check_alive(t_table *table, long now)
{
	int	i;
	int	min_meals;
	
	pthread_mutex_lock(&(table->philos->m_philo));
	if (ft_time(table->philos->last_meal) > table->die_time)
	{
		print_log("%d %i died\n", now, table->philos->id);
		table->philos->alive = 0;
		table->end_flag = 1;
	}
	pthread_mutex_unlock(&(table->philos->m_philo));
	if (table->meals_limit)
	{
		i = 0;
		min_meals = table->total_meals[i];
		while (++i < table->philos_count)
			if (min_meals > table->total_meals[i])
				min_meals = table->total_meals[i];
		if (min_meals >= table->meals_limit)
			table->end_flag = 1;
	}
}

static void	end_brainstorm(t_table *table)
{
	t_philo	*temp_philo;
	t_philo	*first;

	end_threads(table);
	temp_philo = table->philos;
	first = table->philos;
	while (temp_philo)
	{
		if (table->philos->next != first)
			temp_philo = table->philos->next;
		else
			temp_philo = NULL;
		pthread_mutex_destroy(&(table->philos->m_philo));
		free(table->philos);
		table->philos = temp_philo;
	}
	free(table);
}
