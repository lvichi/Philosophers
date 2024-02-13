/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:03:23 by lvichi            #+#    #+#             */
/*   Updated: 2024/02/13 16:02:46 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		init_processes(t_table *table);
static void	init_semaphores(t_table *table);
static void	philo_routine(t_table *table);
static void	*philo_control(void * data);
static void	*philo_end(void * data);
// static void	*routine(void *data);
// static void	start_next_thread(t_philo *philo);
// static void	eat_routine(t_philo *philo);
// static void	get_fork_right(t_philo *philo);

void	init_processes(t_table *table)
{
	int 	i;
	
	i = -1;
	init_semaphores(table);
	while (++i < table->philos_count)
	{
		if (!fork())
		{
			(table->philo).id = i + 1;
			(table->philo).sem_philo_name = sem_format_name((table->philo).id);
			sem_unlink((table->philo).sem_philo_name);
			(table->philo).sem_philo = sem_open((table->philo).sem_philo_name,
					O_CREAT, O_RDWR, 1);
			(table->philo).last_meal = ft_time(0);
			philo_routine(table);
			break;
		}
		usleep(1000);
	}
	if ((table->philo).id == 0)
		print_table(table);
}

static void	init_semaphores(t_table *table)
{
	sem_unlink("/sem_print");
	table->sem_print = sem_open("/sem_print", O_CREAT, O_RDWR, 1);
	sem_unlink("/sem_forks");
	(table->philo).sem_forks = sem_open("/sem_forks", O_CREAT, O_RDWR,
			table->philos_count);
	sem_unlink("/sem_end");
	table->sem_end = sem_open("/sem_end", O_CREAT, O_RDWR, 0);
	sem_unlink("/sem_full");
	table->sem_full = sem_open("/sem_full", O_CREAT, O_RDWR, 0);
}

static void	philo_routine(t_table *table)
{
	pthread_create(&((table->philo).control_thread), NULL, philo_control,
			table);
	pthread_create(&((table->philo).end_thread), NULL, philo_end, table);
	while (1)
	{
		sem_wait((table->philo).sem_forks);
		print_log(table, 1);
		sem_wait((table->philo).sem_forks);
		print_log(table, 1);
		sem_wait((table->philo).sem_philo);
		(table->philo).last_meal = ft_time(0);
		if (!(table->philo).alive)
			break;
		sem_post((table->philo).sem_philo);
		print_log(table, 2);
		usleep((table->philo).eat_time * 1000);
		sem_post((table->philo).sem_forks);
		sem_post((table->philo).sem_forks);
		sem_wait((table->philo).sem_philo);
		(table->philo).meals_count++;
		sem_post((table->philo).sem_philo);
		print_log(table, 3);
		usleep((table->philo).sleep_time * 1000);
		print_log(table, 4);
	}
	sem_post((table->philo).sem_philo);
	sem_post((table->philo).sem_forks);
	sem_post((table->philo).sem_forks);
	pthread_join((table->philo).control_thread, NULL);
	pthread_join((table->philo).end_thread, NULL);
	sem_close(table->sem_print);
	sem_close(table->sem_full);
	sem_close(table->sem_end);
	sem_close((table->philo).sem_forks);
	sem_close((table->philo).sem_philo);
	sem_unlink((table->philo).sem_philo_name);
	free((table->philo).sem_philo_name);
}

static void	*philo_control(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (1)
	{
		ft_time(table->start_time);
		sem_wait((table->philo).sem_philo);
		if (ft_time((table->philo).last_meal) > table->die_time ||
				!(table->philo).alive)
			break ;
		if ((table->philo).meals_count == table->meals_limit)
		{
			sem_post(table->sem_full);
			(table->philo).meals_count++;
		}
		sem_post((table->philo).sem_philo);
		usleep(100);
	}
	sem_post((table->philo).sem_philo);
	print_log(table, 5);
	i = 0;
	while (i++ < table->philos_count)
		sem_post(table->sem_end);
	sem_wait((table->philo).sem_philo);
	(table->philo).alive = 0;
	sem_post((table->philo).sem_philo);
	sem_post((table->philo).sem_forks);
	return (NULL);
}

static void	*philo_end(void * data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	sem_wait(table->sem_end);
	sem_wait((table->philo).sem_philo);
		(table->philo).alive = 0;
	sem_post((table->philo).sem_philo);
	sem_post(table->sem_end);
	i = -1;
	while (++i < table->philos_count)
		sem_post(table->sem_full);
	return (NULL);
}

/*static void	start_next_thread(t_philo *philo)
{
	usleep(100);
	if ((philo->next)->id != 1)
	{
		pthread_mutex_lock(&((philo->next)->m_philo));
		(philo->next)->last_meal = ft_time(0);
		pthread_mutex_unlock(&((philo->next)->m_philo));
		pthread_create(&((philo->next)->thread), NULL, routine, philo->next);
	}
}

static void	eat_routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->m_philo));
		if (philo->fork || !philo->alive)
		{
			philo->fork = 0;
			philo->got_fork++;
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->m_philo);
		usleep(1000);
	}
	get_fork_right(philo);
	pthread_mutex_lock(&(philo->m_philo));
	((t_philo *)philo)->eating++;
	((t_philo *)philo)->last_meal = ft_time(0);
	pthread_mutex_unlock(&(philo->m_philo));
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(&(philo->m_philo));
	philo->fork = 1;
	pthread_mutex_unlock(&(philo->m_philo));
	pthread_mutex_lock(&((philo->next)->m_philo));
	(philo->next)->fork = 1;
	pthread_mutex_unlock(&((philo->next)->m_philo));
}

static void	get_fork_right(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&((philo->next)->m_philo));
		if ((philo->next)->fork)
		{
			(philo->next)->fork = 0;
			pthread_mutex_unlock(&((philo->next)->m_philo));
			pthread_mutex_lock(&philo->m_philo);
			philo->got_fork++;
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&((philo->next)->m_philo));
		pthread_mutex_lock(&philo->m_philo);
		if (!philo->alive)
		{
			pthread_mutex_unlock(&philo->m_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->m_philo);
		usleep(1000);
	}
}*/
