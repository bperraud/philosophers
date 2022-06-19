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
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->var->mutex);
	printf("thread id: %li\n", philo->thread_id);
	pthread_mutex_unlock(&philo->var->mutex);
	return (NULL);
	while (!philo->dead)
	{
		eat(philo);
		think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_philo	**philos;

	if (argc < 5 || argc > 6)
		return (-1);

	philos = init_struct(argc, argv);
	if (!philos)
		return (-1);
	i = -1;
	while (i++ < philos[0]->var->n_philo - 1)
		pthread_create(&(philos[i]->thread_id), NULL, launch_thread, philos[i]);
	i = -1;
	while (++i <philos[0]->var->n_philo)
		pthread_join(philos[i]->thread_id, NULL);

	free(philos[0]->var);
	free_philos(philos[0]->var->n_philo, philos);
	return (0);
}
