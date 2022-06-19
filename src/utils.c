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

# include "philo.h"

static int	space(const char *str, int i)
{
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	res;

	neg = 1;
	res = 0;
	i = space(str, 0);
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

t_philo	**free_philos(int index, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}

t_philo	**free_var(t_var *var)
{
	free(var);
	return (NULL);
}

