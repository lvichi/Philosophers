/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:11:24 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/12 20:23:04 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_table(t_table *table, char **argv);

void	create_table(t_table *table, char **argv)
{
	t_philo	philo;
	
	table->philos_count = ft_atoi(argv[0]);
	table->start_time = ft_time(0);
	table->die_time = ft_atoi(argv[1]);
	table->meals_limit = -1;
	if (argv[4])
		table->meals_limit = ft_atoi(argv[4]);
	philo.id = 0;
	philo.alive = 1;
	philo.eat_time = ft_atoi(argv[2]);
	philo.sleep_time = ft_atoi(argv[3]);
	philo.meals_count = 0;
	philo.last_meal = 0;
	table->philo = philo;
}
