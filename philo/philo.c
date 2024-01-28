/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/28 21:15:53 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	start_routine(t_table *table);
static int	check_input(char **argv);

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
		write (2, "Wrong arguments, only numbers between 1 and INT_MAX\n", 52);
	else if (create_table(&table, &argv[1]))
		write (2, "Failed to create philosophers\n", 30);
	else if (start_routine(table))
		write (2, "Failed to start routine\n", 24);
	else
	{
		print_table(table);
		mutex_destroy(&table);
		free_table(table);
	}
}

static int	start_routine(t_table *table)
{
	if (mutex_init(&table))
		return (1);
	if (thread_init(&table))
	{
		mutex_destroy(&table);
		return (1);
	}
	return (0);
}

static int	check_input(char **argv)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9' || j > 10)
				return (1);
	}
	i = -1;
	while (argv[++i])
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) == 0)
			return (1);
	return (0);
}
