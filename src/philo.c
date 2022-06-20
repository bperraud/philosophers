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
	if (philo->var->n_must_eat && philo->meal_eaten == philo->var->n_must_eat)
		return ;

	if (philo->left_fork_index < philo->right_fork_index)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		print_action(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, FORK);
	}

	//time to eat
	print_action(philo, EAT);
	sleep_ms(philo->var->time_to_eat);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->var);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);

	sleeping(philo);
	print_action(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	//time to sleep
	print_action(philo, SLEEP);
	sleep_ms(philo->var->time_to_sleep);
}
