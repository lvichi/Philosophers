/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 16:06:29 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);
static int	start_routine(t_table *table);
static int	start_brainstorm(t_table *table);
static void check_alive(t_table **table, int *end_flag, int *now);
static int	end_brainstorm(t_table *table);

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
		write (2, "Wrong arguments, only numbers between 1 and INT_MAX\n", 52);
	else if (create_table(&table, &argv[1]))
		write (2, "Failed to create philosophers\n", 30);
	else if (start_routine(table))
		write (2, "Failed to start routine\n", 24);
	else
	{
		start_brainstorm(table);
		end_brainstorm(table);
		mutex_destroy(&table);
		free_table(table);
	}
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

static int	start_routine(t_table *table)
{
	if (mutex_init(&table))
		return (1);
	if (thread_init(&table))
	{
		mutex_destroy(&table);
		return (1);
	}
	return (0);
}

static int	start_brainstorm(t_table *table)
{
	int	end_flag;
	int now;
	
	end_flag = 0;
	while (1)
	{
		now = ft_time(table->start_time);
		pthread_mutex_lock(&(table->data));
		if (!table->philos->alive)
			break ;
		if (table->philos->thinking && !end_flag && table->philos->thinking--)
			ft_printf("%d ms\t %d is thinking\n", now, table->philos->id);
		while (table->philos->got_fork && !end_flag && table->philos->got_fork--)
			ft_printf("%d ms\t %d has taken a fork\n", now, table->philos->id);
		check_alive(&table, &end_flag, &now);
		if (table->philos->eating && !end_flag && table->philos->eating--)
			ft_printf("%d ms\t %d is eating\n", now, table->philos->id);
		if (table->philos->sleeping && !end_flag && table->philos->sleeping--)
			ft_printf("%d ms\t %d is sleeping\n", now, table->philos->id);
		pthread_mutex_unlock(&(table->data));
		table->philos = table->philos->next;
	}
	pthread_mutex_unlock(&(table->data));
	return (0);
}

static void check_alive(t_table **table, int *end_flag, int *now)
{
	int	id_start;
	int	meals_limit_count;

	if (ft_time((*table)->philos->last_meal) > (*table)->die_time || *end_flag)
	{
		if (!(*end_flag))
			ft_printf("%d ms\t %d died\n", *now, (*table)->philos->id);
		*end_flag = 1;
		(*table)->philos->alive = 0;
	}
	id_start = (*table)->philos->id;
	meals_limit_count = 0;
	while ((*table)->meals_limit > 0)
	{
		if ((*table)->philos->meals_count >= (*table)->meals_limit)
			meals_limit_count++;
		if (meals_limit_count == (*table)->philos_count)
			*end_flag = 1;
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == id_start)
			break ;
	}
}

static int	end_brainstorm(t_table *table)
{
	int	start;

	start = table->philos->id;
	while (1)
	{
		pthread_join(table->philos->thread, NULL);
		table->philos = table->philos->next;
		if (table->philos->id == start)
			break ;
	}
	return (0);
}
