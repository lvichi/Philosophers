/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/28 21:15:52 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

int	thread_init(t_table **table);
int	mutex_init(t_table **table);
int	mutex_destroy(t_table **table);

int	thread_init(t_table **table)
{
	int	error_flag;

	error_flag = 0;
	while(1)
	{
		pthread_create(&((*table)->philos->thread), NULL, routine, ((*table)->philos)) /////HERE HERE HERE
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
}

int	mutex_init(t_table **table)
{
	int	error_flag;
	
	if (pthread_mutex_init(&((*table)->print), NULL))
		return (1);
	error_flag = 0;
	while (1)
	{
		if (pthread_mutex_init(&((*table)->philos->fork), NULL))
			error_flag = 1;
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
	if (error_flag)
		pthread_mutex_destroy(&((*table)->print))
	while (error_flag)
	{
		pthread_mutex_destroy(&((*table)->philos->fork))
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
	return (0);
}

int	mutex_destroy(t_table **table)
{
	if (pthread_mutex_destroy(&((*table)->print)))
		return (1);
	while (1)
	{
		if (pthread_mutex_destroy(&((*table)->philos->fork)))
			return (1);
		(*table)->philos = (*table)->philos->next;
		if ((*table)->philos->id == 0)
			break ;
	}
	return (0);
}
