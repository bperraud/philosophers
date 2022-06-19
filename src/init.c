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

# include "philo.h"

t_philo	*init_philo(t_var *var, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal = 0;
	philo->n_eaten = 0;
	philo->dead = 0;
	philo->index = index;
	philo->var = var;
	philo->right_fork_index = index;
	if (!index == var->n_philo)
		philo->left_fork_index = index + 1;
	else
		philo->left_fork_index = 1;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
		return (NULL);
	return (philo);
}

static t_philo	**init_philo_thread(t_var *var)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * var->n_philo);
	if (!philos)
		return (NULL);
	philos[var->n_philo + 1] = NULL;
	i = 0;
	while (i < var->n_philo)
	{
		philos[i] = init_philo(var, i + 1);
		if (!philos[i])
			return (free_philos(i, philos));
		if (i != 0)
			philos[i]->left_fork = &(philos[i - 1]->right_fork);
		i++;
	}
	philos[0]->left_fork = &(philos[i - 1]->right_fork);
	return (philos);
}

t_philo	**init_struct(int argc, char **argv)
{
	t_var	*var;
	t_philo	**philos;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->n_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var->n_must_eat = ft_atoi(argv[5]);
	else
		var->n_must_eat = 0;
	if (var->n_philo <= 0 || var->time_to_die < 0
		|| var->time_to_eat < 0 || var->time_to_sleep < 0)
		return (free_var(var));
	if (pthread_mutex_init(&var->std_mutex, NULL) != 0)
		return (NULL);
	gettimeofday(&var->t0, NULL);
	philos = init_philo_thread(var);
	if (!philos)
		return (free_var(var));
	return (philos);
}
