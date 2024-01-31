/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:49:11 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 15:13:16 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*routine(void *data);
static void	get_fork(t_philo *philo, int side);

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(philo->data);
	while (philo->alive)
	{
		pthread_mutex_unlock(philo->data);
		get_fork(philo, 1);
		get_fork(philo, 2);
		pthread_mutex_lock(philo->data);
		philo->eating++;
		philo->last_meal = ft_time(0);
		pthread_mutex_unlock(philo->data);
		usleep(philo->eat_time * 1000);
		pthread_mutex_lock(philo->data);
		(philo->next)->fork = 1;
		philo->fork = 1;
		philo->sleeping++;
		philo->meals_count++;
		pthread_mutex_unlock(philo->data);
		usleep(philo->sleep_time * 1000);
		pthread_mutex_lock(philo->data);
		philo->thinking++;
	}
	pthread_mutex_unlock(philo->data);
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
