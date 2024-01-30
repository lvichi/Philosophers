/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:26:05 by lvichi            #+#    #+#             */
/*   Updated: 2024/01/30 20:59:58 by lvichi           ###   ########.fr       */
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
	int				eat_time;
	int				sleep_time;
	int				meals_count;
	int				alive;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				die_time;
	int				meals_limit;
	pthread_mutex_t	print;
}	t_table;

// table.c
int		create_table(t_table **table, char **argv);
void	free_table(t_table *table);
// routine.c
void	*routine(void *data);
// threads.c
int		thread_init(t_table **table);
int		mutex_init(t_table **table);
void	mutex_destroy(t_table **table);
// utils.c
void	*ft_calloc(size_t nmemb, size_t size);
size_t	array_len(char **array);
size_t	str_len(char *str);
long	ft_atoi(char *nptr);
void	ft_putnbr(long nbr);

#endif /* philo.h */