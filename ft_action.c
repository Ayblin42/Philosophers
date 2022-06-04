/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:16:55 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/04 16:42:22 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->rfork);
	print_state_change(D_FORK, p);
	pthread_mutex_lock(&p->lfork);
	print_state_change(D_FORK, p);
	print_state_change(D_EAT, p);
	p->last_meal = get_time();
	sleep_check(p->s->time_to_eat, p->s);
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
