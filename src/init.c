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

t_philo	*init_philo(int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal = 0;
	philo->n_eaten = 0;
	philo->dead = 0;
	philo->index = index;
	//philo->right_dirty = 1;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
		return (NULL);
	return (philo);
}

static t_var	*init_philo_thread(t_var *var)
{
	int	i;

	var->philos = malloc(sizeof(t_philo) * var->n_philo);
	if (!var->philos)
		return (NULL);
	memset(var->philos, 0, sizeof(t_philo) * var->n_philo);
	i = 0;
	while (i < var->n_philo)
	{
		var->philos[i] = init_philo(i + 1);
		if (!var->philos[i])
			return (free_tab(i, var));
		if (i != 0)
		{
			var->philos[i]->left_fork = &(var->philos[i - 1]->right_fork);
			//var->philos[i]->left_dirty = &(var->philos[i - 1]->right_dirty);
		}
		i++;
	}
	var->philos[0]->left_fork = &(var->philos[i - 1]->right_fork);
	//var->philos[0]->left_dirty = &(var->philos[i - 1]->right_dirty);
	return (var);
}

int	check_positif(t_var *var)
{
	return (var->n_philo <= 0 || var->time_to_die < 0
		|| var->time_to_eat < 0 || var->time_to_sleep < 0);
}

t_var	*init_struct(int argc, char **argv)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->philos = NULL;
	var->n_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var->n_must_eat = ft_atoi(argv[5]);
	else
		var->n_must_eat = 0;
	if (check_positif(var))
		return (free_var(var));
	if (!init_philo_thread(var))
		return (free_var(var));
	return (var);
}
