/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/31 15:13:37 by lvichi           ###   ########.fr       */
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
		if ((*table)->philos->id == 1)
			break ;
		usleep(100);
	}
	return (error_flag);
}

int	mutex_init(t_table **table)
{
	int				error_flag;

	error_flag = pthread_mutex_init(&((*table)->data), NULL);
	while (1 && !error_flag)
	{
		(*table)->philos->data = &((*table)->data);
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 1)
			break ;
	}
	if (error_flag)
		mutex_destroy(table);
	return (error_flag);
}

void	mutex_destroy(t_table **table)
{
	pthread_mutex_destroy(&((*table)->data));
}
