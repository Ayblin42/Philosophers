/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:47:28 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 02:04:33 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_kill(t_philo *philo)
{
	printf("%lu %d philo died\n", get_time(), philo->id + 1);
	philo->s->status = DEAD;
}

static int	philo_dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal) >= philo->s->time_to_die)
	{
		philo_kill(philo);
		pthread_mutex_unlock(philo->s->lock);
		return (1);
	}
	return (0);
}

int	death_checker_norminette(t_philo **philo, t_settings *s, int i, int full)
{
	while (i < s->philo_nb)
	{
		pthread_mutex_lock(s->lock);
		pthread_mutex_lock(s->meal);
		if (philo[i]->meal_count == philo[i]->meal_to_take)
		{
			pthread_mutex_unlock(s->meal);
			++full;
			if (full == s->philo_nb)
			{
				if (philo_dead(philo[i]))
					return (1);
				pthread_mutex_unlock(s->lock);
				return (1);
			}
		}
		else
			pthread_mutex_unlock(s->meal);
		if (philo_dead(philo[i]))
			return (1);
		pthread_mutex_unlock(s->lock);
		i++;
	}
	return (0);
}

void	death_checker(t_philo **philo, t_settings *s)
{
	while (1)
	{
		if (death_checker_norminette (philo, s, 0, 0))
			return ;
		usleep(200);
	}
}
