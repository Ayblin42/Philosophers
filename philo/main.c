/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:24:50 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/24 22:57:09 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tv;
	static long int	start_time = -2;

	if (start_time == -2)
	{
		gettimeofday(&tv, NULL);
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

static void	nb_eat_checker(t_settings *s, t_philo **p)
{
	int	i;

	i = 0;
	while (i < s->philo_nb)
	{
		if (p[i]->meal_count < s->meal_nb)
			break ;
		i++;
		if (i == s->philo_nb)
			s->all_ate = 1;
	}
}

void	death_checker(t_settings *s, t_philo **p)
{
	int	i;

	while (!(s->all_ate))
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
		if (s->meal_nb != -1)
			nb_eat_checker(s, p);
	}
}

int	invalid_argument(char **av)
{
	int	i;
	int	n;

	i = 0;
	while (av[++i])
	{
		if (!str_is_num(av[i]))
			return (0);
		n = ft_atoi(av[i]);
		if (n == -1 || n == 0)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_settings	s;
	t_philo		**p;
	int			i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (ft_error("invalid number of arguments .\n", 2));
	if (!invalid_argument(av))
		return (ft_error("Invalid arguments .\n", 2));
	init_settings(&s, av, ac);
	p = init_philo(&s);
	if (s.philo_nb > 1)
		death_checker(&s, p);
	while (i < s.philo_nb)
	{
		pthread_join(p[i]->thread_id, NULL);
		free(p[i]);
		i++;
	}
	free(p);
}
