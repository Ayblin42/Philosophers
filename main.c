/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:24:50 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/02 19:05:40 by ayblin           ###   ########.fr       */
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
	if (p->id % 2)
		usleep(p->s->time_to_eat);
	while(1)
	{
		philo_eat(p);
		philo_sleep(p);
		philo_think(p);
	}
	return (0);
}

void	death_checker(t_rules *r, t_philosopher *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dieded))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}
