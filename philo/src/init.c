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

#include "philo.h"

static t_philo	*init_philo(t_table *table, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal_time = get_time(table);
	philo->meal_eaten = 0;
	philo->index = index;
	philo->table = table;
	philo->left_dirty = 0;
	if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
		return (NULL);
	return (philo);
}

t_philo	**init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	if (!table)
		return (NULL);
	philos = malloc(sizeof(t_philo *) * table->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->n_philo)
	{
		philos[i] = init_philo(table, i + 1);
		if (!philos[i])
			return (free_philos(i, philos));
		if (i != 0)
		{
			philos[i]->right_fork = &(philos[i - 1]->left_fork);
			philos[i]->right_dirty = &(philos[i - 1]->left_dirty);
		}
		i++;
	}
	philos[0]->right_fork = &(philos[i - 1]->left_fork);
	philos[0]->right_dirty = &(philos[i - 1]->left_dirty);
	return (philos);
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
	table->simulation_end = 0;
	if (argc == 6)
		table->n_must_eat = ft_atoi(argv[5]);
	else
		table->n_must_eat = 0;
	if (table->n_philo <= 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0
		|| table->n_must_eat < 0)
		return (free_table(table));
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0
		|| pthread_mutex_init(&table->end_mutex, NULL) != 0)
		return (free_table(table));
	gettimeofday(&table->t0, NULL);
	return (table);
}
