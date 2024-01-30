/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:49:11 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/30 20:59:45 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data);

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(&philo->data);
	while (1 && philo->alive)
	{
		pthread_mutex_unlock(&philo->data);
		philo->meals_count++;
		usleep(philo->eat_time);
		usleep(philo->sleep_time);
		pthread_mutex_lock(&philo->data);
	}
	pthread_mutex_unlock(&philo->data);
	return (NULL);
}
