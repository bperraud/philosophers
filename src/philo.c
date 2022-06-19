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
	if (philo->var->n_must_eat && philo->n_eaten == philo->var->n_must_eat)
		return ;

	if (philo->left_fork_index < philo->left_fork_index)
	{
		print_action(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
	}

	//time to eat
	print_action(philo, EAT);
	sleep_ms(philo->var->time_to_eat);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);

	//time to sleep
	print_action(philo, SLEEP);
	sleep_ms(philo->var->time_to_sleep);

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
