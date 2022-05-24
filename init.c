/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:47:28 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/23 13:24:16 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo    **init_philo(t_settings *s)
{
    t_philo    **p;
    int        i;

    p = (t_philo **)malloc(sizeof(t_philo) * s->philo_nb);
    if (!p)
        return (NULL);
    pthread_mutex_init(&s->write, NULL);
    i = -1;
    while (++i < s->philo_nb)
    {
        p[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!p[i])
            return (NULL);
		p[i]->s= s;
        p[i]->id = i;
        p[i]->last_meal = 0;
		pthread_mutex_init(&p[i]->lfork, NULL);
    }
    i = -1;
   while (++i < s->philo_nb)
    {
        if (i < s->philo_nb - 1)
            p[i]->rfork = &p[i + 1]->lfork;
        else
            p[i]->rfork = &p[0]->lfork;
        if (pthread_create(&p[i]->thread_id, NULL, &routine, p[i]) != 0)
            return (NULL); //faut exit et free ici
    }
    return (p);
}

void    init_settings(t_settings *s, char **av)
{
    int i;

    i = 0;
    s->philo_nb = ft_atoi(av[1]);
	s->time_to_die = ft_atoi(av[2]);
	s->time_to_eat = ft_atoi(av[3]);
	s->time_to_sleep = ft_atoi(av[4]);
	s->fork = malloc(sizeof(int) * s->philo_nb);
    while (i < s->philo_nb)
    {
        s->fork[i] = 0;
        i++;
    }
}
