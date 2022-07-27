/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:24:50 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 02:28:39 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long unsigned int time_in_ms, t_philo *philo)
{
	long unsigned int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms && is_philo_alive(philo))
		usleep(50);
}

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
		if (n <= 0)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_settings	*s;
	t_philo		**p;
	int			i;

	i = 0;
	if ((ac != 5 && ac != 6) || !invalid_argument(av))
		return (ft_error("invalid arguments .\n", 2));
	s = malloc(sizeof(t_settings));
	init_settings(s, av);
	p = init_philo(s, av, ac);
	launch(s, p);
	while (i < s->philo_nb)
	{
		pthread_join(p[i]->thread_id, NULL);
		free(p[i]);
		i++;
	}
	free(p);
	free(s->meal);
	free(s->lock);
	free(s);
}
