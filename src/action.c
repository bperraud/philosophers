/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:55:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/20 16:55:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	unlock_after_death(t_philo *philo)
{
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
}

void	eat(t_philo *philo)
{
	if (philo->var->n_must_eat && philo->meal_eaten == philo->var->n_must_eat)
		return ;

	if (philo->left_fork_index < philo->right_fork_index)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (unlock_after_death(philo))
			return;
		print_action(philo, LEFT_FORK);
		pthread_mutex_lock(philo->right_fork);
		if (unlock_after_death(philo))
			return;
		print_action(philo, RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (unlock_after_death(philo))
			return;
		print_action(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->left_fork);
		if (unlock_after_death(philo))
			return;
		print_action(philo, LEFT_FORK);
	}

	//time to eat
	//check death
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}

	print_action(philo, EAT);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->var);
	sleep_ms(philo->var->time_to_eat);

	if (philo->left_fork_index < philo->right_fork_index)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}

	//pthread_mutex_unlock(philo->left_fork);
	//pthread_mutex_unlock(&philo->right_fork);

	sleeping(philo);
	print_action(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	//time to sleep
	print_action(philo, SLEEP);
	sleep_ms(philo->var->time_to_sleep);
}

void	print_action(t_philo *philo, int action)
{
	if (philo->var->simulation_end)
		return ;
	pthread_mutex_lock(&philo->var->std_mutex);
	if (!philo->dead)
	{
		printf("%d ", get_time(philo->var));
		if (action == RIGHT_FORK)
			printf("%s%d has taken right fork\n", CYAN, philo->index);
		else if (action == LEFT_FORK)
			printf("%s%d has taken left fork\n", CYAN, philo->index);
		else if (action == EAT)
			printf("%s%d is eating\n", GREEN, philo->index);
		else if (action == SLEEP)
			printf("%s%d is sleeping\n", MAGENTA, philo->index);
		else if (action == THINK)
			printf("%s%d is thinking\n", YELLOW, philo->index);
	}
	else if (action == DIE)
	{
		printf("%d ", get_time(philo->var));
		printf("%s%d died\n", RED, philo->index);
	}
	printf(RESET);
	pthread_mutex_unlock(&philo->var->std_mutex);
}
