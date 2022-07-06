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

#include "philo_bonus.h"

static int	check_death(t_philo *philo)
{
	if (get_time(philo->table) - philo->last_meal_time > philo->table->time_to_die)
	{
		exit(philo->index);
	}
	return 0;
}

static void	*launch_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		usleep(50);
		if (get_time(philo->table) - philo->last_meal_time > philo->table->time_to_die)
		{
			exit(philo->index);
		}
	}
	return (NULL);
}

/*
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
*/

static void	new_philo(int index, t_table *table)
{
	t_philo	*philo;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		philo = init_philo(index, table);
		pthread_create(&philo->thread, NULL, launch_thread, philo);
		//while (!check_death(philo))
		while (1)
		{
			eat(philo);
			if (philo->meal_eaten == philo->table->n_must_eat)
				break ;
		}
		exit(0);
	}
	return ;
}

int	philo(int argc, char **argv)
{
	int		i;
	int		status;
	int		dead_philo;
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (-1);
	i = 0;
	while (i++ < table->n_philo)
	{
		new_philo(i, table);
	}

	//wait_for_death(table, philos);

	waitpid(-1, &status, 0);
	dead_philo = WEXITSTATUS(status);
	while( wait(NULL) > 0)
		;
	print_end(dead_philo, table);
	free(table->philo_pid);
	free(table);
	return (1);
}
