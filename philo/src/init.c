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

static t_philo	*init_philo(t_var *var, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal_time = get_time(var);
	philo->meal_eaten = 0;
	philo->index = index;
	philo->var = var;
	philo->left_dirty = 0;
	if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
		return (NULL);
	return (philo);
}

t_philo	**init_philos(t_var *var)
{
	t_philo	**philos;
	int		i;

	if (!var)
		return (NULL);
	philos = malloc(sizeof(t_philo *) * var->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < var->n_philo)
	{
		philos[i] = init_philo(var, i + 1);
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

t_var	*init_var(int argc, char **argv)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->n_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	var->simulation_end = 0;
	if (argc == 6)
		var->n_must_eat = ft_atoi(argv[5]);
	else
		var->n_must_eat = 0;
	if (var->n_philo <= 0 || var->time_to_die < 0
		|| var->time_to_eat < 0 || var->time_to_sleep < 0)
		return (free_var(var));
	if (pthread_mutex_init(&var->std_mutex, NULL) != 0
		|| pthread_mutex_init(&var->end_mutex, NULL) != 0)
		return (NULL);
	gettimeofday(&var->t0, NULL);
	return (var);
}
