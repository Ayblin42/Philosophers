/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:47:28 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/25 18:02:07 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch(t_settings *s, t_philo	**p)
{
	int	i;

	i = -1;
	while (++i < s->philo_nb)
	{
		if (i < s->philo_nb - 1)
			p[i]->rfork = &p[i + 1]->lfork;
		else
			p[i]->rfork = &p[0]->lfork;
		if (pthread_create(&p[i]->thread_id, NULL, &routine, p[i]) != 0)
			return (0);
	}
	return (0);
}

t_philo	**init_philo(t_settings *s)
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
		p[i]->s = s;
		p[i]->id = i;
		p[i]->last_meal = 0;
		p[i]->meal_count = 0;
		p[i]->time_to_die = s->time_to_die;
		p[i]->time_to_eat = s->time_to_eat;
		p[i]->time_to_sleep = s->time_to_sleep;
		p[i]->philo_nb = s->philo_nb;
		p[i]->meal_nb = s->meal_nb;
		pthread_mutex_init(&p[i]->lfork, NULL);
	}
	launch(s, p);
	return (p);
}

void	init_settings(t_settings *s, char **av, int ac)
{
	int	i;

	i = -1;
	s->philo_nb = ft_atoi(av[1]);
	s->time_to_die = ft_atoi(av[2]);
	s->time_to_eat = ft_atoi(av[3]);
	s->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		s->meal_nb = ft_atoi(av[5]);
	else
		s->meal_nb = -1;
	s->died = 0;
	s->all_ate = 0;
	s->fork = malloc(sizeof(char) * s->philo_nb);
	while(++i < s->philo_nb)
	{
		printf("|%i\n",i);
		s->fork[i] = 1;
	}
	pthread_mutex_init(&s->write, NULL);
	pthread_mutex_init(&s->death_check, NULL);
	pthread_mutex_init(&s->meal_check, NULL);
}
