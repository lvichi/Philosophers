/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/13 18:50:51 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		philo_routine(t_table *table);
static void	*philo_control(void *data);
static void	philo_control_end(t_table *table);
static void	*philo_end(void *data);
static void	philo_end_routine(t_table *table);

void	philo_routine(t_table *table)
{
	pthread_create(&((table->philo).control_thread), 0, philo_control, table);
	while (1)
	{
		sem_wait((table->philo).sem_forks);
		print_log(table, 1);
		sem_wait((table->philo).sem_forks);
		print_log(table, 1);
		sem_wait((table->philo).sem_philo);
		(table->philo).last_meal = ft_time(0);
		if (!(table->philo).alive)
			break ;
		sem_post((table->philo).sem_philo);
		print_log(table, 2);
		usleep((table->philo).eat_time * 1000);
		sem_post((table->philo).sem_forks);
		sem_post((table->philo).sem_forks);
		sem_wait((table->philo).sem_philo);
		(table->philo).meals_count++;
		sem_post((table->philo).sem_philo);
		print_log(table, 3);
		usleep((table->philo).sleep_time * 1000);
		print_log(table, 4);
		usleep(100);
	}
	philo_end_routine(table);
}

static void	*philo_control(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	pthread_create(&((table->philo).end_thread), 0, philo_end, table);
	while (1)
	{
		ft_time(table->start_time);
		sem_wait((table->philo).sem_philo);
		if (ft_time((table->philo).last_meal) > table->die_time
			|| !(table->philo).alive)
			break ;
		if ((table->philo).meals_count == table->meals_limit)
		{
			sem_post(table->sem_full);
			(table->philo).meals_count++;
		}
		sem_post((table->philo).sem_philo);
		usleep(100);
	}
	sem_post((table->philo).sem_philo);
	philo_control_end(table);
	return (NULL);
}

static void	philo_control_end(t_table *table)
{
	int		i;

	print_log(table, 5);
	sem_wait((table->philo).sem_philo);
	(table->philo).alive = 0;
	sem_post((table->philo).sem_philo);
	i = 0;
	while (i++ < table->philos_count)
		sem_post(table->sem_end);
	sem_post((table->philo).sem_forks);
}

static void	*philo_end(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	sem_wait(table->sem_end);
	sem_wait((table->philo).sem_philo);
	(table->philo).alive = 0;
	sem_post((table->philo).sem_philo);
	sem_post(table->sem_end);
	i = -1;
	while (++i < table->philos_count)
		sem_post(table->sem_full);
	return (NULL);
}

static void	philo_end_routine(t_table *table)
{
	sem_post((table->philo).sem_philo);
	sem_post((table->philo).sem_forks);
	sem_post((table->philo).sem_forks);
	pthread_join((table->philo).control_thread, NULL);
	pthread_join((table->philo).end_thread, NULL);
	sem_close(table->sem_print);
	sem_close(table->sem_full);
	sem_close(table->sem_end);
	sem_close((table->philo).sem_forks);
	sem_close((table->philo).sem_philo);
	sem_unlink((table->philo).sem_philo_name);
	free((table->philo).sem_philo_name);
}
