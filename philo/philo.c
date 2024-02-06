/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/04 17:57:53 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);
static void	start_brainstorm(t_table *table);
static void	check_alive(t_table **table, int *end_flag, long *now);
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
	int		end_flag;
	long	now;

	end_flag = 0;
	while (1)
	{
		now = ft_time(table->start_time);
		pthread_mutex_lock(&(table->philos->m_fork));
		if (!table->philos->alive)
			break ;
		if (table->philos->thinking && !end_flag && table->philos->thinking--)
			print_log("%d %i is thinking\n", now, table->philos->id);
		while (table->philos->got_fork && !end_flag
			&& table->philos->got_fork--)
			print_log("%d %i has taken a fork\n", now, table->philos->id);
		pthread_mutex_unlock(&(table->philos->m_fork));
		check_alive(&table, &end_flag, &now);
		pthread_mutex_lock(&(table->philos->m_fork));
		if (table->philos->eating && !end_flag && table->philos->eating--)
			print_log("%d %i is eating\n", now, table->philos->id);
		if (table->philos->sleeping && !end_flag && table->philos->sleeping--)
			print_log("%d %i is sleeping\n", now, table->philos->id);
		pthread_mutex_unlock(&(table->philos->m_fork));
		table->philos = table->philos->next;
	}
	pthread_mutex_unlock(&(table->philos->m_fork));
	end_brainstorm(table);
}

static void	check_alive(t_table **table, int *end_flag, long *now)
{
	int	id_start;
	int	meals_limit_count;

	pthread_mutex_lock(&((*table)->philos->m_fork));
	if (ft_time((*table)->philos->last_meal) > (*table)->die_time || *end_flag)
	{
		if (!(*end_flag))
			print_log("%d %i died\n", *now, (*table)->philos->id);
		*end_flag = 1;
		(*table)->philos->alive = 0;
	}
	id_start = (*table)->philos->id;
	meals_limit_count = 0;
	pthread_mutex_unlock(&((*table)->philos->m_fork));
	while ((*table)->meals_limit > 0)
	{
		pthread_mutex_lock(&((*table)->philos->m_fork));
		if ((*table)->philos->meals_count >= (*table)->meals_limit)
			meals_limit_count++;
		if (meals_limit_count == (*table)->philos_count)
			*end_flag = 1;
		pthread_mutex_unlock(&((*table)->philos->m_fork));
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == id_start)
			break ;
	}
}

static void	end_brainstorm(t_table *table)
{
	t_philo	*temp_philo;
	t_philo	*first;

	end_threads(table);
	//pthread_mutex_destroy(&(table->data));
	temp_philo = table->philos;
	first = table->philos;
	while (temp_philo)
	{
		if (table->philos->next != first)
			temp_philo = table->philos->next;
		else
			temp_philo = NULL;
		pthread_mutex_destroy(&(table->philos->m_fork));
		free(table->philos);
		table->philos = temp_philo;
	}
	free(table);
}
