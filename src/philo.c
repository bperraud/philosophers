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


void	eat(t_philo *philo)
{
	if (philo->n_eaten == philo->var->n_must_eat)
		return ;

	pthread_mutex_lock(&philo->var->mutex);
	if (philo->left_fork)


	pthread_mutex_unlock(&philo->var->mutex);

	return ;
}


void	think(t_philo *philo)
{
	return ;
}

void	p_sleep(t_philo *philo)
{
	return ;
}
