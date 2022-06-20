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

void	*launch_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!check_death(philo))
	{
		eat(philo);
	}
	return (NULL);
}

static void wait_for_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->var->end_mutex);
		if (philo->var->simulation_end)
		{
			pthread_mutex_unlock(&philo->var->end_mutex);
			pthread_mutex_lock(&philo->var->std_mutex);
			printf("%d ", get_time(philo->var));
			printf("%s%d died\n", RED, philo->var->dead_philo_index);
			printf(RESET);
			pthread_mutex_unlock(&philo->var->std_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->var->end_mutex);
	}
}

int	philo(int argc, char **argv)
{
	int		i;
	t_philo	**philos;

	philos = init_struct(argc, argv);
	if (!philos)
		return (-1);
	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
		pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);

	wait_for_death(philos[0]);

	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
		pthread_join(philos[i]->thread_id, NULL);
	free(philos[0]->var);
	free_philos(philos[0]->var->n_philo, philos);
	return (1);
}

int	check_death(t_philo *philo)
{
	//if (philo->dead)
		//return (1);
	pthread_mutex_lock(&philo->var->end_mutex);
	if (philo->var->simulation_end)
	{
		pthread_mutex_unlock(&philo->var->end_mutex);

		return (1);
	}
	pthread_mutex_unlock(&philo->var->end_mutex);
	if (get_time(philo->var) - philo->last_meal_time > philo->var->time_to_die)
	{
		//philo->dead = 1;

		//pthread_mutex_unlock(&philo->left_fork);
		//pthread_mutex_unlock(philo->right_fork);


		pthread_mutex_lock(&philo->var->end_mutex);
		philo->var->simulation_end = 1;
		pthread_mutex_unlock(&philo->var->end_mutex);
		philo->var->dead_philo_index = philo->index;
		return (1);
	}
	return (0);
}
