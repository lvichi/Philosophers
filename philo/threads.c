/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/04 19:08:48 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init_threads(t_table *table);
static void	*routine(void *philo);
static void	get_fork_left(t_philo *philo);
static void	get_fork_right(t_philo *philo);
void		end_threads(t_table *table);

int	init_threads(t_table *table)
{
	int	error_flag;

	error_flag = pthread_mutex_init(&(table->data), NULL);
	while (!error_flag)
	{
		table->philos->data = &(table->data);
		error_flag = pthread_mutex_init(&(table->philos->m_fork), NULL);
		table->philos = table->philos->next;
		if (table->philos->id == 1)
			break ;
		usleep(100);
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
		if ((((t_philo *)philo)->id) % 2 == 0)
		{
			get_fork_left((t_philo *)philo);
			usleep(100);
			get_fork_right((t_philo *)philo);
		}
		else
		{
			get_fork_right((t_philo *)philo);
			usleep(100);
			get_fork_left((t_philo *)philo);
		}
		pthread_mutex_lock(((t_philo *)philo)->data);
		((t_philo *)philo)->eating++;
		((t_philo *)philo)->last_meal = ft_time(0);
		pthread_mutex_unlock(((t_philo *)philo)->data);
		usleep(((t_philo *)philo)->eat_time * 1000);
		pthread_mutex_lock(&((((t_philo *)philo)->next)->m_fork));
		(((t_philo *)philo)->next)->fork = 1;
		pthread_mutex_unlock(&((((t_philo *)philo)->next)->m_fork));
		pthread_mutex_lock(&((t_philo *)philo)->m_fork);
		((t_philo *)philo)->fork = 1;
		pthread_mutex_unlock(&((t_philo *)philo)->m_fork);
		pthread_mutex_lock(((t_philo *)philo)->data);
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

static void	get_fork_left(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->m_fork);
		if (philo->fork)
		{
			philo->fork = 0;
			pthread_mutex_unlock(&philo->m_fork);
			pthread_mutex_lock(philo->data);
			philo->got_fork++;
			break ;
		}
		else
			pthread_mutex_unlock(&philo->m_fork);
		pthread_mutex_lock(philo->data);
		if (!philo->alive)
			break ;
		pthread_mutex_unlock(philo->data);
	}
	pthread_mutex_unlock(philo->data);
}

static void	get_fork_right(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&((philo->next)->m_fork));
		if ((philo->next)->fork)
		{
			(philo->next)->fork = 0;
			pthread_mutex_unlock(&((philo->next)->m_fork));
			pthread_mutex_lock(philo->data);
			philo->got_fork++;
			break ;
		}
		else
			pthread_mutex_unlock(&((philo->next)->m_fork));
		pthread_mutex_lock(philo->data);
		if (!philo->alive)
			break ;
		pthread_mutex_unlock(philo->data);
	}
	pthread_mutex_unlock(philo->data);
}

void	end_threads(t_table *table)
{
	int		start;

	start = table->philos->id;
	while (1)
	{
		pthread_join(table->philos->thread, NULL);
		table->philos = table->philos->next;
		if (table->philos->id == start)
			break ;
	}
}
