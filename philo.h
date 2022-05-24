/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:28:52 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/23 11:38:35 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

# define D_FORK 0
# define D_EAT 1
# define D_SLEEP 2
# define D_THINK 3
# define D_DEATH 4

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_settings
{
	int	        philo_nb;
	int	        time_to_die;
	int	        time_to_eat;
	int	        time_to_sleep;
	int		*fork;
	pthread_mutex_t write;
}			t_settings;

typedef struct s_philo
{
	t_settings			*s;
	int					id;
	long int			last_meal;
	int					meal_count;
	pthread_t			thread_id;
	pthread_mutex_t		lfork;
	pthread_mutex_t		*rfork;
}		t_philo;

t_philo				**init_philo(t_settings *s);
void				*routine(void *arg);
void				init_settings(t_settings *s, char **av);
long int			get_time(void);
void				print_state_change(int	state, t_philo *p);

#endif
