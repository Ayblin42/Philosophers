/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:16:55 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/07 19:57:59 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(p->s->time_to_eat);
	while(!(p->s->died))
	{
		philo_eat(p);
		if (p->s->all_ate)
			break ;
		philo_sleep(p);
		philo_think(p);
	}
	return (0);
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->rfork);
	print_state_change(D_FORK, p);
	pthread_mutex_lock(&p->lfork);
	print_state_change(D_FORK, p);
	print_state_change(D_EAT, p);
	p->last_meal = get_time();
	sleep_check(p->s->time_to_eat, p->s);
	(p->meal_count)++;
	pthread_mutex_unlock(&p->lfork);
	pthread_mutex_unlock(p->rfork);
}

void	philo_sleep(t_philo *p)
{
	print_state_change(D_SLEEP, p);
	sleep_check(p->s->time_to_sleep, p->s);
}

void	philo_think(t_philo *p)
{
	print_state_change(D_THINK, p);
}

void	sleep_check(int	time_to_sleep, t_settings *s)
{
	long long int	i;

	i = get_time();
	while (!s->died)
	{
		if (time_to_sleep < (get_time() - i))
			break ;
		usleep(50);
	}
}
