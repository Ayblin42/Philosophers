/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:46:12 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 01:07:42 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			write(fd, &s[i++], 1);
}

int	ft_error(char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

int	is_philo_alive(t_philo	*philo)
{
	pthread_mutex_lock(philo->s->lock);
	if (philo->s->status != ALIVE)
	{
		pthread_mutex_unlock(philo->s->lock);
		return (DEAD);
	}
	pthread_mutex_unlock(philo->s->lock);
	return (ALIVE);
}
