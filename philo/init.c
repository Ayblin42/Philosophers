/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:47:28 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 02:40:26 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch(t_settings *s, t_philo **p)
{
	int	i;

	i = -1;
	get_time();
	if (s->philo_nb == 1)
		return (philo_one(p[0]), 0);
	while (++i < s->philo_nb)
	{
		if (i < s->philo_nb - 1)
			p[i]->rfork = &p[i + 1]->lfork;
		else
			p[i]->rfork = &p[0]->lfork;
		if (pthread_create(&p[i]->thread_id, NULL, &routine, p[i]) != 0)
			return (0);
	}
	death_checker(p, s);
	return (0);
}

t_philo	**init_philo(t_settings *s, char **av, int ac)
{
	t_philo		**p;
	int			i;

	p = (t_philo **)malloc(sizeof(t_philo) * s->philo_nb);
	if (!p)
		return (NULL);
	i = -1;
	while (++i < s->philo_nb)
	{
		p[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!p[i])
			return (NULL);
		if (ac == 6)
			p[i]->meal_to_take = ft_atoi(av[5]);
		else
			p[i]->meal_to_take = -1;
		p[i]->meal_count = 0;
		p[i]->s = s;
		p[i]->id = i;
		p[i]->last_meal = 0;
		pthread_mutex_init(&p[i]->lfork, NULL);
	}
	return (p);
}

void	init_settings(t_settings *s, char **av)
{
	s->philo_nb = ft_atoi(av[1]);
	s->time_to_die = ft_atoi(av[2]);
	s->time_to_eat = ft_atoi(av[3]);
	s->time_to_sleep = ft_atoi(av[4]);
	s->finish = 0;
	s->status = ALIVE;
	s->meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(s->meal, NULL);
	s->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(s->lock, NULL);
}
