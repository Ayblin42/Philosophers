/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:16:55 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 02:35:12 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	print_state_change(philo, "is sleeping");
	ft_usleep(philo->s->time_to_sleep, philo);
}

int	eating(t_philo *philo)
{
	if (philo_take_fork(philo) == 1)
		return (1);
	print_state_change(philo, "is eating");
	pthread_mutex_lock(philo->s->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->s->lock);
	ft_usleep(philo->s->time_to_eat, philo);
	pthread_mutex_lock(philo->s->lock);
	pthread_mutex_lock(philo->s->meal);
	philo->meal_count++;
	pthread_mutex_unlock(philo->s->meal);
	pthread_mutex_unlock(philo->s->lock);
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}

int	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->rfork);
	else
		pthread_mutex_lock(&philo->lfork);
	print_state_change(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->lfork))
		{
			pthread_mutex_unlock(philo->rfork);
			return (1);
		}
		print_state_change(philo, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philo->rfork))
		{
			pthread_mutex_unlock(&philo->lfork);
			return (1);
		}
		print_state_change(philo, "has taken a fork");
	}
	return (0);
}

void	*philo_one(t_philo *philo)
{
	printf("%lu %d has taken a fork\n", get_time(), philo->id + 1);
	ft_usleep(philo->s->time_to_die, philo);
	printf("%lu %d philo died\n", get_time(), philo->id + 1);
	return (NULL);
}

void	*routine(void	*philo_data)
{
	t_philo	*philo;

	philo = philo_data;
	if (philo->id % 2)
		ft_usleep((philo->s->time_to_eat) - 5, philo);
	while (is_philo_alive(philo) == ALIVE)
	{
		if (philo->meal_count == philo->meal_to_take)
			return (NULL);
		eating(philo);
		if (is_philo_alive(philo) != ALIVE)
			return (NULL);
		sleeping(philo);
		if (is_philo_alive(philo) != ALIVE)
			return (NULL);
		print_state_change(philo, "is thinking");
		if (is_philo_alive(philo) != ALIVE)
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
