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

static void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (get_time(philo->table) - philo->last_meal_time
			> philo->table->time_to_die)
		{
			free(philo);
			exit(philo->index);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	new_philo(int index, t_table *table)
{
	t_philo	*philo;
	pid_t	pid;

	pid = fork();
	table->philo_pid[index - 1] = pid;
	usleep(20);
	if (pid == 0)
	{
		philo = init_philo(index, table);
		pthread_create(&philo->thread, NULL, check_death, philo);
		while (1)
		{
			eat(philo);
			if (philo->meal_eaten == philo->table->n_must_eat)
			{
				free(philo);
				exit(0);
			}
		}
	}
}

static void	kill_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		if (table->philo_pid[i] != 0)
			kill(table->philo_pid[i], SIGKILL);
	}
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
		new_philo(i, table);
	waitpid(-1, &status, 0);
	dead_philo = WEXITSTATUS(status);
	if (dead_philo)
	{
		kill_all(table);
		print_end(dead_philo, table);
	}
	else
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	free_table(table);
	return (0);
}
