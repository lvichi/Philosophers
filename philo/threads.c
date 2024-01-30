/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/30 20:58:58 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		thread_init(t_table **table);
int		mutex_init(t_table **table);
void	mutex_destroy(t_table **table);

int	thread_init(t_table **table)
{
	int	error_flag;

	error_flag = 0;
	while (1 && !error_flag)
	{
		error_flag = pthread_create(&((*table)->philos->thread),
				NULL, routine, ((*table)->philos));
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
	return (error_flag);
}

int	mutex_init(t_table **table)
{
	int				error_flag;

	error_flag = pthread_mutex_init(&(*table)->print, NULL);
	while (1 && !error_flag)
	{
		error_flag = pthread_mutex_init(&((*table)->philos->fork), NULL);
		if (error_flag)
			break ;
		error_flag = pthread_mutex_init(&((*table)->philos->data), NULL);
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
	if (error_flag)
		mutex_destroy(table);
	return (error_flag);
}

void	mutex_destroy(t_table **table)
{
	int	start;

	start = (*table)->philos->id;
	pthread_mutex_destroy((&((*table)->print)));
	while (1)
	{
		pthread_mutex_destroy(&((*table)->philos->fork));
		pthread_mutex_destroy(&((*table)->philos->data));
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == start)
			break ;
	}
}
