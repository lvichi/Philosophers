/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:26:05 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/04 17:56:58 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	int				alive;
	int				eat_time;
	int				sleep_time;
	int				meals_count;
	long			last_meal;
	int				fork;
	int				got_fork;
	int				eating;
	int				sleeping;
	int				thinking;
	pthread_t		thread;
	pthread_mutex_t	*data;
	pthread_mutex_t	m_fork;
	struct s_philo	*next;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				philos_count;
	long			start_time;
	int				die_time;
	int				meals_limit;
	pthread_mutex_t	data;
}	t_table;

// table.c
int		create_table(t_table **table, char **argv);
// threads.c
int		init_threads(t_table *table);
void	end_threads(t_table *table);
// utils.c
long	ft_time(int start);
long	ft_atoi(char *nptr);
void	print_log(const char *format, int time, int id);

#endif