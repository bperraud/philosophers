/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:51:14 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/19 18:51:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philo(int index, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal_time = get_time(table);
	philo->meal_eaten = 0;
	philo->index = index;
	philo->table = table;
	philo->simulation_end = 0;
	return (philo);
}

static int	setup_semaphores(t_table *table)
{
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	sem_unlink("sem_end");
	table->sem_print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (table->sem_print == SEM_FAILED)
		return (1);
	table->sem_forks = sem_open("sem_forks", O_CREAT | O_EXCL, 0644,
			table->n_philo / 2);
	if (table->sem_forks == SEM_FAILED)
		return (1);
	table->sem_end = sem_open("sem_end", O_CREAT | O_EXCL, 0644, 1);
	if (table->sem_end == SEM_FAILED)
		return (1);
	return (0);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->n_must_eat = ft_atoi(argv[5]);
	else
		table->n_must_eat = 0;
	if (setup_semaphores(table))
		return (free_table(table));
	if (table->n_philo <= 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (free_table(table));
	table->philo_pid = malloc(sizeof(int) * table->n_philo);
	if (!table->philo_pid)
		return (free_table(table));
	gettimeofday(&table->t0, NULL);
	return (table);
}
