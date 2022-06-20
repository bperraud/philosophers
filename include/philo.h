/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:13:02 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/16 22:13:02 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define RESET "\e[0m"

typedef struct timeval	t_time;

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_var
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	int				simulation_end;
	t_time			t0;
	pthread_mutex_t	std_mutex;
	pthread_mutex_t end_mutex;
}					t_var;

typedef struct s_philo
{
	int				index;
	atomic_int		last_meal_time;
	atomic_int		meal_eaten;
	atomic_int		dead;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	int				left_fork_index;
	int				right_fork_index;
	t_var			*var;
}					t_philo;

/* utils */
int		ft_atoi(const char *str);
t_philo	**free_philos(int index, t_philo **philos);
t_philo	**free_var(t_var *var);
void	sleep_ms(int ms);
void	print_action(t_philo *philo, int action);
int		get_time(t_var *var);

/* init */
t_philo	**init_struct(int argc, char **argv);

/* philo action */
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	sleeping(t_philo *philo);
int		check_death(t_philo *philo);

#endif
