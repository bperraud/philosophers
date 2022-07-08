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

#include "philo_bonus.h"

int	eat(t_philo *philo)
{
	sem_wait(philo->table->sem_forks);
	print_action(philo, FORK);
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->table);
	sleep_ms(philo->table->time_to_eat);
	sem_post(philo->table->sem_forks);
	if (philo->meal_eaten == philo->table->n_must_eat)
		return (1);
	print_action(philo, SLEEP);
	sleep_ms(philo->table->time_to_sleep);
	print_action(philo, THINK);
	return (0);
}

void	print_action(t_philo *philo, int action)
{
	sem_wait(philo->table->sem_print);
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
	sem_post(philo->table->sem_print);
}

void	print_end(int dead_philo, t_table *table)
{
	printf(RESET);
	printf("%d ", get_time(table));
	printf("%s%d died\n", RED, dead_philo);
}
