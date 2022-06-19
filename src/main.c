/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:16:11 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/13 23:16:11 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_thread(void *arg)
{
	t_var	*var;
	t_philo	*philo;

	var = (t_var *) arg;
	pthread_mutex_lock(&var->mutex);
	philo = var->philos[var->philo_id - 1];
	var->philo_id++;
	pthread_mutex_unlock(&var->mutex);
	while (!philo->dead)
	{
		eat(philo, var);
		think(philo, var);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_var	*var;

	if (argc < 5 || argc > 6)
		return (-1);

	var = init_struct(argc, argv);
	if (!var)
		return (-1);
	while (++i <var->n_philo)
		pthread_create(&(var->philos[i]->thread_id), NULL, launch_thread, var);
	//wait_for_death(var);

	while (++i < var->n_philo)
		pthread_join(var->philos[i]->thread_id, NULL);


	return (0);
}
