/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:13:05 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/16 22:13:05 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void	*launch_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	usleep(1000);
	while (!check_death(philo))
	{
		eat(philo);
	}
	return (NULL);
}

static void	print_end(t_var *var)
{
	pthread_mutex_lock(&var->end_mutex);
	if (var->simulation_end)
	{
		usleep(1);
		pthread_mutex_unlock(&var->end_mutex);
		pthread_mutex_lock(&var->std_mutex);
		printf("%d ", get_time(var));
		printf("%s%d died\n", RED, var->dead_philo_index);
		printf(RESET);
		pthread_mutex_unlock(&var->std_mutex);
		return ;
	}
	pthread_mutex_unlock(&var->end_mutex);
}

static void wait_for_death(t_var *var, t_philo **philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (i++ < var->n_philo - 1)
		{
			if (check_death(philos[i]))
				return ;
			i++;
		}
	}
}

int	philo(int argc, char **argv)
{
	int		i;
	t_philo	**philos;
	t_var	*var;

	var =  init_var(argc, argv);
	philos = init_philos(var);
	if (!philos)
		return (-1);
	i = -1;
	while (i++ < var->n_philo - 1)
	{
		if (i%2 == 0)
			pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);
	}

	i = -1 ;
	while (i++ < var->n_philo - 1)
	{
		if (i%2 != 0)
			pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);
	}

	wait_for_death(var, philos);
	print_end(var);
	i = -1;
	while (i++ < var->n_philo - 1)
		pthread_join(philos[i]->thread_id, NULL);
	free(var);
	free_philos(var->n_philo, philos);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->end_mutex);
	if (philo->var->simulation_end)
	{
		pthread_mutex_unlock(&philo->var->end_mutex);
		return (1);
	}
	if (get_time(philo->var) - philo->last_meal_time > philo->var->time_to_die)
	{
		philo->var->simulation_end = 1;
		pthread_mutex_unlock(&philo->var->end_mutex);
		philo->var->dead_philo_index = philo->index;
		return (1);
	}
	pthread_mutex_unlock(&philo->var->end_mutex);
	return (0);
}
