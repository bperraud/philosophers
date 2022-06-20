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

int	philo(int argc, char **argv)
{
	int		i;
	t_philo	**philos;

	philos = init_struct(argc, argv);
	if (!philos)
		return (-1);
	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
	{
		if (i%2 == 0)
			pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);
	}
	sleep_ms(1);
	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
	{
		if (i%2 != 0)
			pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);
	}
	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
		pthread_join(philos[i]->thread_id, NULL);
	free(philos[0]->var);
	free_philos(philos[0]->var->n_philo, philos);
}

int	check_death(t_philo *philo)
{
	if (philo->dead)
		return (1);
	if (philo->var->simulation_end)
	{
		return (1);
	}
	if (get_time(philo->var) - philo->last_meal_time > philo->var->time_to_die)
	{
		philo->dead = 1;
		print_action(philo, DIE);
		philo->var->simulation_end = 1;
		return (1);
	}
	return (0);
}
