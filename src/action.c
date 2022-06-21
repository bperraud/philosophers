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

static void	sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	sleep_ms(philo->var->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_action(philo, THINK);
}

static	int	can_pick_left(t_philo *philo)
{

	if (philo->var->n_philo % 2 == 1 && philo->index == philo->var->n_philo)
	{
		return (philo->left_dirty && !*philo->right_dirty);
	}
	if ((philo->index%2 == 0 && philo->left_dirty)
		|| (philo->index%2 != 0 && !philo->left_dirty))
	{
		return (1);
	}
	return (0);
}

static	int	can_pick_right(t_philo *philo)
{
	if (philo->var->n_philo % 2 == 1 && philo->index == philo->var->n_philo)
	{
		return (philo->left_dirty && !*philo->right_dirty);
	}
	if ((philo->index%2 == 0 && *philo->right_dirty)
		|| (philo->index%2 != 0 && !*philo->right_dirty))
	{
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	if (philo->var->n_must_eat && philo->meal_eaten == philo->var->n_must_eat)
		return ;
	if (can_pick_left(philo) && can_pick_right(philo))
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->left_fork);
		print_action(philo, LEFT_FORK);
	}
	else
		return ;

	//time to eat
	print_action(philo, EAT);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->var);
	sleep_ms(philo->var->time_to_eat);

	philo->left_dirty = !philo->left_dirty;
	*philo->right_dirty = !*philo->right_dirty;

	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

	//time to sleep
	sleeping(philo);
	//time to think
	thinking(philo);
}

void	print_action(t_philo *philo, int action)
{
	/*
	pthread_mutex_lock(&philo->var->end_mutex);
	if (philo->var->simulation_end)
	{
		pthread_mutex_unlock(&philo->var->end_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->var->end_mutex);
	*/
	pthread_mutex_lock(&philo->var->std_mutex);
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
	printf(RESET);
	pthread_mutex_unlock(&philo->var->std_mutex);
}
