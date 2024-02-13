/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/13 18:55:55 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);
static void	init_processes(t_table *table);
static void	end_routine(t_table *table);
static void	*meals_limit_control(void *data);

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
	{
		if (check_input(&argv[1]) == 1)
			write (2, "Only numbers between 1 and INT_MAX\n", 35);
		else
		{
			write(1, "Number maximum of philosophers: ", 32);
			ft_putnbr(PHILO_MAX);
			write(1, "\n", 1);
		}
	}
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
	if (ft_atoi(argv[++i]) > PHILO_MAX)
		return (2);
	while (argv[++i])
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) == 0)
			return (1);
	return (0);
}

static void	init_processes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos_count)
	{
		if (!fork())
		{
			(table->philo).id = i + 1;
			(table->philo).sem_philo_name = sem_format_name((table->philo).id);
			sem_unlink((table->philo).sem_philo_name);
			(table->philo).sem_philo = sem_open((table->philo).sem_philo_name,
					O_CREAT, O_RDWR, 1);
			(table->philo).last_meal = ft_time(0);
			philo_routine(table);
			break ;
		}
		usleep(100);
	}
	if ((table->philo).id == 0)
		end_routine(table);
}

static void	end_routine(t_table *table)
{
	if (table->meals_limit > 0)
		pthread_create(&table->full_thread, 0, meals_limit_control, table);
	while (1)
		if (waitpid(-1, NULL, 0) <= 0)
			break ;
	if (table->meals_limit > 0)
		pthread_join(table->full_thread, NULL);
	sem_close(table->sem_print);
	sem_unlink("/sem_print");
	sem_close(table->sem_full);
	sem_unlink("/sem_full");
	sem_close(table->sem_end);
	sem_unlink("/sem_end");
	sem_close((table->philo).sem_forks);
	sem_unlink("/sem_forks");
}

static void	*meals_limit_control(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	i = -1;
	while (++i < table->philos_count)
		sem_wait(table->sem_full);
	i = -1;
	while (++i < table->philos_count)
	{
		sem_post(table->sem_end);
		sem_post((table->philo).sem_forks);
	}
	return (NULL);
}
