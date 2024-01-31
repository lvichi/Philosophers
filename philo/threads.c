/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 22:54:39 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init_threads(t_table *table);
static void	*routine(void *philo);
static void	get_fork(t_philo *philo, int side);

int	init_threads(t_table *table)
{
	int	error_flag;

	error_flag = pthread_mutex_init(&(table->data), NULL);
	while (!error_flag)
	{
		table->philos->data = &(table->data);
		table->philos = table->philos->next;
		if (table->philos->id == 1)
			break ;
		usleep(50);
	}
	while (!error_flag)
	{
		error_flag = pthread_create(&(table->philos->thread),
				NULL, routine, table->philos);
		table->philos = table->philos->next;
		if (table->philos->id == 1)
			break ;
	}
	if (error_flag)
		pthread_mutex_destroy(&(table->data));
	return (error_flag);
}

void	*routine(void *philo)
{
	while (1)
	{
		get_fork((t_philo *)philo, 1);
		get_fork((t_philo *)philo, 2);
		pthread_mutex_lock(((t_philo *)philo)->data);
		((t_philo *)philo)->eating++;
		((t_philo *)philo)->last_meal = ft_time(0);
		pthread_mutex_unlock(((t_philo *)philo)->data);
		usleep(((t_philo *)philo)->eat_time * 1000);
		pthread_mutex_lock(((t_philo *)philo)->data);
		(((t_philo *)philo)->next)->fork = 1;
		((t_philo *)philo)->fork = 1;
		((t_philo *)philo)->sleeping++;
		((t_philo *)philo)->meals_count++;
		pthread_mutex_unlock(((t_philo *)philo)->data);
		usleep(((t_philo *)philo)->sleep_time * 1000);
		pthread_mutex_lock(((t_philo *)philo)->data);
		((t_philo *)philo)->thinking++;
		if (!(((t_philo *)philo)->alive))
			break ;
		pthread_mutex_unlock(((t_philo *)philo)->data);
	}
	pthread_mutex_unlock(((t_philo *)philo)->data);
	return (NULL);
}

static void	get_fork(t_philo *philo, int side)
{
	while (side == 1)
	{
		pthread_mutex_lock(philo->data);
		if (philo->fork || !philo->alive)
		{
			philo->fork = 0;
			philo->got_fork++;
			break ;
		}
		pthread_mutex_unlock(philo->data);
	}
	while (side == 2)
	{
		pthread_mutex_lock(philo->data);
		if ((philo->next)->fork || !philo->alive)
		{
			(philo->next)->fork = 0;
			philo->got_fork++;
			break ;
		}
		pthread_mutex_unlock(philo->data);
	}
	pthread_mutex_unlock(philo->data);
}
