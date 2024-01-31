/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:49:11 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 00:21:36 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*routine(void *data);
static void	get_fork(t_philo *philo);

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(&philo->data);
	while (philo->alive)
	{
		pthread_mutex_unlock(&philo->data);
		get_fork(philo);
		usleep(philo->eat_time * 1000);
		pthread_mutex_lock(&(philo->next)->data);
		(philo->next)->fork = 1;
		pthread_mutex_unlock(&(philo->next)->data);
		pthread_mutex_lock(&philo->data);
		philo->fork = 1;
		philo->sleep++;
		philo->meals_count++;
		pthread_mutex_unlock(&philo->data);
		usleep(philo->sleep_time * 1000);
		pthread_mutex_lock(&philo->data);
		philo->thinking++;
	}
	pthread_mutex_unlock(&philo->data);
	return (NULL);
}

static void	get_fork(t_philo *philo)
{
	int	forks_count;
	
	forks_count = 0;
	while (forks_count < 2)
	{
		pthread_mutex_lock(&philo->data);
		if (!philo->alive)
			forks_count = 2;
		if (philo->fork)
		{
			philo->fork = 0;
			philo->got_fork++;
			forks_count++;
		}
		pthread_mutex_unlock(&philo->data);
		pthread_mutex_lock(&(philo->next)->data);
		if ((philo->next)->fork)
		{
			philo->fork = 0;
			philo->got_fork++;
			forks_count++;
		}
		pthread_mutex_unlock(&(philo->next)->data);
	}
}
