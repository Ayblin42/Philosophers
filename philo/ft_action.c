/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:16:55 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/24 22:51:10 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->philo_nb == 1)
	{
		print_state_change(D_FORK, p);
		usleep(p->time_to_die * 1000);
		pthread_mutex_lock(&p->s->death_check);
		p->s->died = 1;
		pthread_mutex_unlock(&p->s->death_check);
		printf("%d %d died\n", p->time_to_die, p->id);
		return (0);
	}
	if (p->id % 2)
		usleep((p->time_to_eat * 1000) - 50);
	pthread_mutex_lock(&p->s->death_check);
	while (!(p->s->died))
	{
		pthread_mutex_unlock(&p->s->death_check);
		if (philo_eat(p))
			return (0);
		if (p->meal_count == p->meal_nb)
			return (0) ;
		if (philo_sleep(p))
			return (0);
		philo_think(p);
		pthread_mutex_lock(&p->s->death_check);
	}
	return (0);
}

int	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->rfork);
	print_state_change(D_FORK, p);
	pthread_mutex_lock(&p->lfork);
	print_state_change(D_FORK, p);
	print_state_change(D_EAT, p);
	p->last_meal = get_time();
	if (p->time_to_die < p->time_to_eat)
		return (1);
	usleep(p->time_to_eat * 1000);
	(p->meal_count)++;
	pthread_mutex_unlock(&p->lfork);
	pthread_mutex_unlock(p->rfork);
	return (0);
}

int	philo_sleep(t_philo *p)
{
	long long int	die;
	long long int	sleep;
	long long int	eat;

	die = p->time_to_die;
	sleep = p->time_to_sleep;
	eat = p->time_to_eat;
	print_state_change(D_SLEEP, p);
	if (die <= (eat + sleep))
		return (1);
	usleep(p->s->time_to_sleep * 1000);
	return (0);
}

void	philo_think(t_philo *p)
{
	print_state_change(D_THINK, p);
}
