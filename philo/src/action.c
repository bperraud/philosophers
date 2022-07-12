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

#include "philo.h"

static	int	can_pick_left(t_philo *philo)
{
	if (philo->table->n_philo % 2 == 1 && philo->index == philo->table->n_philo)
	{
		return (philo->left_dirty && !*philo->right_dirty);
	}
	if ((philo->index % 2 == 0 && philo->left_dirty)
		|| (philo->index % 2 != 0 && !philo->left_dirty))
	{
		return (1);
	}
	return (0);
}

static	int	can_pick_right(t_philo *philo)
{
	if (philo->table->n_philo % 2 == 1 && philo->index == philo->table->n_philo)
	{
		return (philo->left_dirty && !*philo->right_dirty);
	}
	if ((philo->index % 2 == 0 && *philo->right_dirty)
		|| (philo->index % 2 != 0 && !*philo->right_dirty))
	{
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	if ((philo->table->n_must_eat && philo->meal_eaten
			== philo->table->n_must_eat) || philo->table->n_philo == 1)
		return ;
	while (!(can_pick_left(philo) && can_pick_right(philo)))
		usleep(50);
	pthread_mutex_lock(philo->right_fork);
	philo->left_dirty = !philo->left_dirty;
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->left_fork);
	*philo->right_dirty = !*philo->right_dirty;
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->table);
	sleep_ms(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	if (philo->meal_eaten == philo->table->n_must_eat)
		return ;
	print_action(philo, SLEEP);
	sleep_ms(philo->table->time_to_sleep);
	print_action(philo, THINK);
}

void	print_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->table->end_mutex);
	if (!philo->table->simulation_end)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf(RESET);
		printf("%d ", get_time(philo->table));
		if (action == FORK)
			printf("%s%d has taken a fork\n", CYAN, philo->index);
		else if (action == EAT)
			printf("%s%d is eating\n", GREEN, philo->index);
		else if (action == SLEEP)
			printf("%s%d is sleeping\n", MAGENTA, philo->index);
		else if (action == THINK)
			printf("%s%d is thinking\n", YELLOW, philo->index);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	pthread_mutex_unlock(&philo->table->end_mutex);
}

void	print_end(t_table *table)
{
	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_lock(&table->end_mutex);
	if (table->simulation_end)
	{
		printf(RESET);
		printf("%d ", get_time(table));
		printf("%s%d died\n", RED, table->dead_philo_index);
	}
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_unlock(&table->end_mutex);
}
