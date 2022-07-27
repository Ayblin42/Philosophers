/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:52:21 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 01:50:40 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_philo *p, char *msg)
{
	long int	time;

	time = get_time();
	pthread_mutex_lock(p->s->lock);
	if (p->s->status == DEAD)
	{
		pthread_mutex_unlock(p->s->lock);
		return ;
	}
	printf("%lu %d %s\n", time, p->id + 1, msg);
	pthread_mutex_unlock(p->s->lock);
}
