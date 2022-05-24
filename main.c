/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:24:50 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/23 13:53:51 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int        get_time(void)
{
        struct timeval  tv;
        static long int start_time = -2;

        if (start_time == -2)
        {
                gettimeofday(&tv, NULL);
                start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }
        gettimeofday(&tv, NULL);
        return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

int	fork_r(t_settings *s, int i)
{
	if ((i + 1) == s->philo_nb)
		return (0);
	else
		return (i);
}

int	main(int ac, char **av)
{
	t_settings	s;
	t_philo	**p;

	init_settings(&s, av);
	p = init_philo(&s);
	(void)p;
	(void)ac;
	while (1)
	{

	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	write(1,"routine\n",8);
	while(1)
	{
		pthread_mutex_lock(&p->lfork);
		pthread_mutex_lock(p->rfork);
			// write(1,"routin1\n",8);
		if (p->s->fork[p->id] == 0 && p->s->fork[fork_r(p->s, p->id)] == 0)
		{
			print_state_change(D_FORK, p);
			print_state_change(D_FORK, p);
			p->s->fork[p->id] = 1;
			p->s->fork[fork_r(p->s, p->id)] = 1;
			// write(1,"caca\n",5);
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			// print_state_change(D_EAT, p);
			write(1,"eat\n",4);
			usleep(p->s->time_to_eat);
			pthread_mutex_lock(&p->lfork);
			pthread_mutex_lock(p->rfork);
			p->s->fork[p->id] = 0;
			p->s->fork[fork_r(p->s, p->id)] = 0;
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			// print_state_change(D_THINK, p);
			write(1,"sleep\n",6);
			usleep(p->s->time_to_sleep);
		}
		else
		{
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
		}

	}
	return (0);
}
