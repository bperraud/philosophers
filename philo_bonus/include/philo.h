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
# include <signal.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <semaphore.h>
# include <fcntl.h>

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

typedef struct s_table
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	int				simulation_end;
	t_time			t0;
	//pthread_mutex_t	std_mutex;
	//pthread_mutex_t	end_mutex;
	sem_t			*sem_print;
	sem_t			*sem_forks;
	sem_t			*sem_dead;
}					t_table;

typedef struct s_philo
{
	int				index;
	atomic_int		last_meal_time;
	atomic_int		meal_eaten;
	pthread_t		thread_id;
	t_table			*table;
}					t_philo;

/* main */
int		philo(int argc, char **argv);

/* utils */
int		ft_atoi(const char *str);
t_table	*free_table(t_table *table);
void	sleep_ms(int ms);
void	print_action(t_philo *philo, int action);
int		get_time(t_table *table);

/* init */
t_table	*init_table(int argc, char **argv);
t_philo	*init_philo(int index, t_table *table);

/* philo action */
void	eat(t_philo *philo);
void	print_end(t_table *table);

#endif
