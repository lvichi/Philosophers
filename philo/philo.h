/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:26:05 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/21 19:20:37 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>

# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				meals;
	int				fork;
	pthread_t		thread;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

// utils.c
void	*ft_calloc(size_t nmemb, size_t size);
size_t	array_len(char **array);
size_t	str_len(char *str);
long	ft_atoi(char *nptr);
void	ft_putnbr(long nbr);
// table.c
t_philo	*create_table(char **argv);
void	print_table(t_philo *philo);
void	free_table(t_philo *philo);

#endif /* philo.h */