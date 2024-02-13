/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:11:24 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/13 17:04:06 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		create_table(t_table *table, char **argv);
static void	init_semaphores(t_table *table);

void	create_table(t_table *table, char **argv)
{
	t_philo	philo;

	table->philos_count = ft_atoi(argv[0]);
	table->start_time = ft_time(0);
	table->die_time = ft_atoi(argv[1]);
	table->meals_limit = -1;
	if (argv[4])
		table->meals_limit = ft_atoi(argv[4]);
	philo.id = 0;
	philo.alive = 1;
	philo.eat_time = ft_atoi(argv[2]);
	philo.sleep_time = ft_atoi(argv[3]);
	philo.meals_count = 0;
	philo.last_meal = 0;
	table->philo = philo;
	init_semaphores(table);
}

static void	init_semaphores(t_table *table)
{
	sem_unlink("/sem_print");
	table->sem_print = sem_open("/sem_print", O_CREAT, O_RDWR, 1);
	sem_unlink("/sem_forks");
	(table->philo).sem_forks = sem_open("/sem_forks", O_CREAT, O_RDWR,
			table->philos_count);
	sem_unlink("/sem_end");
	table->sem_end = sem_open("/sem_end", O_CREAT, O_RDWR, 0);
	sem_unlink("/sem_full");
	table->sem_full = sem_open("/sem_full", O_CREAT, O_RDWR, 0);
}
