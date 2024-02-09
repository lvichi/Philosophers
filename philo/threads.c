/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/09 17:25:14 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init_threads(t_table *table);
void		*routine(void *data);
static void get_forks(t_philo *philo);
static void	get_fork_left(t_philo *philo);
static void	get_fork_right(t_philo *philo);
void		end_threads(t_table *table);

int	init_threads(t_table *table)
{
	int	error_flag;

	error_flag = 0;
	while (!error_flag)
	{
		error_flag = pthread_mutex_init(&(table->philos->m_philo), NULL);
		table->philos = table->philos->next;
		if (table->philos->id == 1)
			break ;
	}
	table->philos->last_meal = ft_time(0);
	error_flag = pthread_create(&(table->philos->thread), NULL, routine,
		table->philos);
	return (error_flag);
}

void	*routine(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	usleep(10);
	if ((philo->next)->id != 1)
	{
		pthread_mutex_lock(&((philo->next)->m_philo));
		(philo->next)->last_meal = ft_time(0);
		pthread_mutex_unlock(&((philo->next)->m_philo));
		pthread_create(&((philo->next)->thread), NULL, routine, philo->next);
	}
	while (1)
	{
		get_forks(philo);
		usleep(philo->eat_time * 1000);
		pthread_mutex_lock(&((philo->next)->m_philo));
		(philo->next)->fork = 1;
		pthread_mutex_unlock(&((philo->next)->m_philo));
		pthread_mutex_lock(&(philo->m_philo));
		if (!philo->alive)
			break ;
		philo->fork = 1;
		philo->sleeping++;
		philo->meals_count++;
		pthread_mutex_unlock(&(philo->m_philo));
		usleep(philo->sleep_time * 1000);
		pthread_mutex_lock(&(philo->m_philo));
		if (!philo->alive)
			break ;
		((t_philo *)philo)->thinking++;
		pthread_mutex_unlock(&(philo->m_philo));
	}
	pthread_mutex_unlock(&(philo->m_philo));
	return (NULL);
}

static void get_forks(t_philo *philo)
{
	if (philo->id > 0)
	{
		get_fork_left(philo);
		get_fork_right(philo);
	}
	else
	{
		get_fork_right(philo);
		get_fork_left(philo);
	}
	pthread_mutex_lock(&(philo->m_philo));
	((t_philo *)philo)->eating++;
	((t_philo *)philo)->last_meal = ft_time(0);
	pthread_mutex_unlock(&(philo->m_philo));
}

static void	get_fork_left(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->m_philo));
		if (philo->fork || !philo->alive)
		{
			philo->fork = 0;
			philo->got_fork++;
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->m_philo);
		usleep(1000);
	}
}

static void	get_fork_right(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&((philo->next)->m_philo));
		if ((philo->next)->fork)
		{
			(philo->next)->fork = 0;
			pthread_mutex_unlock(&((philo->next)->m_philo));
			pthread_mutex_lock(&philo->m_philo);
			philo->got_fork++;
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&((philo->next)->m_philo));
		pthread_mutex_lock(&philo->m_philo);
		if (!philo->alive)
		{
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->m_philo);
		usleep(1000);
	}
}

void	end_threads(t_table *table)
{
	int		start;

	pthread_mutex_lock(&(table->philos->m_philo));
	start = table->philos->id;
	pthread_mutex_unlock(&(table->philos->m_philo));
	while (1)
	{
		pthread_mutex_lock(&(table->philos->m_philo));
		table->philos->alive = 0;
		pthread_mutex_unlock(&(table->philos->m_philo));
		pthread_join(table->philos->thread, NULL);
		table->philos = table->philos->next;
		if (table->philos->id == start)
			break ;
	}
}
