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

#include "philo.h"

static int	check_death(t_philo *philo)
{
	/*
	pthread_mutex_lock(&philo->table->end_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->end_mutex);
		return (1);
	}
	if (get_time(philo->table) - philo->last_meal_time > philo->table->time_to_die)
	{
		philo->table->simulation_end = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		philo->table->dead_philo_index = philo->index;
		return (1);
	}
	pthread_mutex_unlock(&philo->table->end_mutex);
	*/
	return (0);
}

static void	*launch_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!check_death(philo))
	{
		eat(philo);
	}
	return (NULL);
}

static int	satiate(t_table *table, t_philo **philos)
{
	int	i;

	i = -1;
	if (!table->n_must_eat)
		return (0);
	while (i++ < table->n_philo - 1)
	{
		if (philos[i]->meal_eaten != table->n_must_eat)
			return (0);
		i++;
	}
	return (1);
}

static void	wait_for_death(t_table *table, t_philo **philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (i++ < table->n_philo - 1)
		{
			if (check_death(philos[i]))
				return ;
			i++;
		}
		if (satiate(table, philos))
			return ;
	}
}

static void	new_philo(int index, t_table *table)
{
	t_philo	*philo;
	pid_t	pid;

	pid = fork();
	if (pid == 0)	//child
	{
		philo = init_philo(index, table);
		while (!check_death(philo))
		{
			eat(philo);
		}
	}
	return ;
}

int	philo(int argc, char **argv)
{
	int		i;
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (-1);
	i = -1;
	while (i++ < table->n_philo - 1)
	{
		new_philo(i, table);
	}
	//wait_for_death(table, philos);
	print_end(table);



	free(table);
	return (1);
}
