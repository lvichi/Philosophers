/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/12 22:33:41 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);
void		print_table(t_table *table);
void		print_philo(t_table *table);
/*static void	start_brainstorm(t_table *table);
static void	check_alive(t_table *table, long now);
static void	end_brainstorm(t_table *table);*/

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
		write (2, "Wrong arguments, only numbers between 1 and INT_MAX\n", 52);
	else
	{
		create_table(&table, &argv[1]);
		init_processes(&table);
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

void print_table(t_table *table)
{
	while (1) 
        if (waitpid(-1, NULL, 0) <= 0)
			break;
	sem_close(table->sem_end);
	sem_unlink("/sem_end");
	sem_close(table->sem_print);
	sem_unlink("/sem_print");
	sem_close((table->philo).sem_forks);
	sem_unlink("/sem_forks");
}

void print_philo(t_table *table)
{
	sem_wait(table->sem_print);
	printf("id: %d\n", (table->philo).id);
	printf("eat_time: %d\n",(table->philo).eat_time);
	printf("sleep_time: %d\n", (table->philo).sleep_time);
	printf("meals_count: %d\n\n", (table->philo).meals_count);
	sem_post(table->sem_print);
	sem_close(table->sem_print);
	sem_close((table->philo).sem_philo);
	sem_unlink((table->philo).sem_philo_name);
	free((table->philo).sem_philo_name);
	usleep((table->philo).id * 1000000);
}

/*static void	start_brainstorm(t_table *table)
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

	first = table->philos;
	while (1)
	{
		pthread_mutex_lock(&(table->philos->m_philo));
		table->philos->alive = 0;
		pthread_mutex_unlock(&(table->philos->m_philo));
		pthread_join(table->philos->thread, NULL);
		table->philos = table->philos->next;
		if (table->philos == first)
			break ;
	}
	temp_philo = table->philos;
	while (temp_philo)
	{
		if (table->philos->next != first)
			temp_philo = table->philos->next;
		else
			temp_philo = NULL;
		pthread_mutex_destroy(&(table->philos->m_philo));
		table->philos = temp_philo;
	}
}*/
