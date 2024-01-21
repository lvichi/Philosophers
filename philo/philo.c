/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:56 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/21 19:20:17 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv);
static int	check_input(char **argv);

int	main(int argc, char **argv)
{
	int		error;
	t_philo	*table;

	error = 0;
	if (argc < 5 || argc > 6)
		write(2, "Invalid number of arguments\n", 28);
	else if (check_input(&argv[1]))
		write (2, "Wrong arguments, only numbers between 1 and INT_MAX\n", 52);
	else
	{
		table = create_table(&argv[1]);
		if (!table)
			write (2, "Failed to create philosophers\n", 30);
		print_table(table);
		free_table(table);
	}
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
