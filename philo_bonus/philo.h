/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:26:05 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/12 21:55:30 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>			// For O_* constants
# include <sys/stat.h>		// For mode constants
# include <sys/wait.h>      // For waitpid
# include <stdio.h> 		//delete

# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	int				alive;
	int				eat_time;
	int				sleep_time;
	int				meals_count;
	long			last_meal;
	pthread_t		control_thread;
	pthread_t		end_thread;
	sem_t			*sem_philo;
	char			*sem_philo_name;
	sem_t			*sem_forks;
}	t_philo;

typedef struct s_table
{
	t_philo			philo;
	int				philos_count;
	long			start_time;
	int				die_time;
	int				meals_limit;
	sem_t			*sem_print;
	sem_t			*sem_full;
	sem_t			*sem_end;
}	t_table;

// table.c
void	create_table(t_table *table, char **argv);
void	print_table(t_table *table); //delete
void	print_philo(t_table *table); //delete
// process.c
void	init_processes(t_table *table);
// utils.c
long	ft_time(int start);
long	ft_atoi(char *nptr);
void	print_log(t_table *table, int type);
int		ft_putnbr(long nbr);
char	*sem_format_name(int id);

#endif