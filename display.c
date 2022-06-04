/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:52:21 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/04 17:47:53 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(int	state, t_philo *p)
{
	long int	time;

	time = get_time();
	if (!p->s->died)
	{
		pthread_mutex_lock(&p->s->write);
		if (state == 0)
			printf("%ld %d has taken a fork\n", time, p->id);
		else if (state == 1)
			printf("%ld %d is eating\n", time, p->id);
		else if (state == 2)
			printf("%ld %d is sleeping\n", time, p->id);
		else if (state == 3)
			printf("%ld %d is thinking\n", time, p->id);
		else if (state == 4)
			printf("%ld %d died\n", time, p->id);
		else
			printf("MERDE");
		pthread_mutex_unlock(&p->s->write);
	}
}
