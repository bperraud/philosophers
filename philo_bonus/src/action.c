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

void	eat(t_philo *philo)
{
	if (philo->table->n_must_eat && philo->meal_eaten == philo->table->n_must_eat)
		return ;

	sem_wait(philo->table->sem_forks);
	print_action(philo, FORK);
	sem_wait(philo->table->sem_forks);
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->meal_eaten += 1;
	philo->last_meal_time = get_time(philo->table);
	sleep_ms(philo->table->time_to_eat);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	if (philo->meal_eaten == philo->table->n_must_eat)
		return ;
	print_action(philo, SLEEP);
	sleep_ms(philo->table->time_to_sleep);
	print_action(philo, THINK);
}

void	print_action(t_philo *philo, int action)
{
	/*
	pthread_mutex_lock(&philo->table->end_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->end_mutex);
	*/
	sem_wait(philo->table->sem_print);
	printf("%d ", get_time(philo->table));
	if (action == FORK)
		printf("%s%d has taken a fork\n", CYAN, philo->index);
	else if (action == EAT)
		printf("%s%d is eating\n", GREEN, philo->index);
	else if (action == SLEEP)
		printf("%s%d is sleeping\n", MAGENTA, philo->index);
	else if (action == THINK)
		printf("%s%d is thinking\n", YELLOW, philo->index);
	printf(RESET);
	sem_post(philo->table->sem_print);
}

void	print_end(t_table *table)
{
	//pthread_mutex_lock(&table->end_mutex);
	if (table->simulation_end)
	{
		usleep(1);
		//pthread_mutex_unlock(&table->end_mutex);
		//pthread_mutex_lock(&table->std_mutex);
		printf("%d ", get_time(table));
		//printf("%s%d died\n", RED, table->dead_philo_index);
		printf(RESET);
		//pthread_mutex_unlock(&table->std_mutex);
		return ;
	}
	//pthread_mutex_unlock(&table->end_mutex);
}
