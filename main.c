/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:24:50 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/04 17:02:36 by ayblin           ###   ########.fr       */
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

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("invalid number of arguments .\n", 2);
		return  0;
	}
	init_settings(&s, av);
	p = init_philo(&s);
	death_checker(&s, p);
	(void)p;
	(void)ac;
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

void	death_checker(t_settings *s, t_philo **p)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < s->philo_nb && !(s->died))
		{
			pthread_mutex_lock(&(s->meal_check));
			if (s->time_to_die < get_time() - p[i]->last_meal)
			{
				print_state_change(D_DEATH, p[i]);
				s->died = 1;
			}
			pthread_mutex_unlock(&(s->meal_check));
			usleep(100);
		}
		if (s->died)
			break ;
		i = 0;
	}
}
