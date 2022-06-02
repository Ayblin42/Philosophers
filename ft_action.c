/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:16:55 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/02 17:51:35 by ayblin           ###   ########.fr       */
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
	usleep(p->s->time_to_eat);
	pthread_mutex_unlock(&p->lfork);
	pthread_mutex_unlock(p->rfork);
}

void	philo_sleep(t_philo *p)
{
	print_state_change(D_SLEEP, p);
	usleep(p->s->time_to_sleep);
}

void	philo_think(t_philo *p)
{
	print_state_change(D_THINK, p);
	usleep(p->s->time_to_sleep);
}
