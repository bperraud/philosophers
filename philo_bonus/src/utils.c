/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:13:00 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/16 22:13:00 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	res;

	neg = 1;
	res = 0;
	i = 0;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res * 10 > INT_MAX) && neg == 1)
			return (-1);
		if ((res * 10 - 1 > INT_MAX) && neg == -1)
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((int)(res * neg));
}

t_table	*free_table(t_table *table)
{
	free(table);
	return (NULL);
}

int	get_time(t_table *table)
{
	t_time	t;
	int		s;
	int		s0;
	int		ms;
	int		ms0;

	if (gettimeofday(&t, NULL) != 0)
		return (0);
	s = t.tv_sec * 1000;
	ms = t.tv_usec / 1000;
	s0 = table->t0.tv_sec * 1000;
	ms0 = table->t0.tv_usec / 1000;
	return (s - s0 + ms - ms0);
}

void	sleep_ms(int ms)
{
	t_time	t0;
	t_time	t;
	long	time0;
	long	time;

	gettimeofday(&t0, NULL);
	gettimeofday(&t, NULL);
	time0 = t0.tv_sec * 1000000 + t0.tv_usec;
	time = t.tv_sec * 1000000 + t.tv_usec;
	while (time - time0 < ms * 1000)
	{
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000000 + t.tv_usec;
		if (time - time0 < ms * 1000 - 50)
			usleep(50);
		else
			usleep(ms / 1000 - (time - time0) / 1000000);
	}
}
