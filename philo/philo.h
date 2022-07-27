/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:28:52 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/21 02:34:45 by ayblin           ###   ########.fr       */
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

# define DEAD 0
# define ALIVE 1

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_settings
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				status;
	int				finish;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*lock;
}			t_settings;

typedef struct s_philo
{
	pthread_t			thread_id;
	t_settings			*s;
	int					id;
	long long int		last_meal;
	int					meal_to_take;
	int					meal_count;
	pthread_mutex_t		lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		death_lock;
}		t_philo;

int					str_is_num(char *str);
int					ft_error(char *str, int ret);
int					ft_atoi(const char *nptr);
t_philo				**init_philo(t_settings *s, char **av, int ac);
int					launch(t_settings *s, t_philo	**p);
void				*routine(void	*philo_data);
void				init_settings(t_settings *s, char **av);
long int			get_time(void);
void				print_state_change(t_philo *p, char *msg);
int					philo_eat(t_philo *p);
int					philo_sleep(t_philo *p);
void				philo_think(t_philo *p);
void				sleep_check(int time_to_sleep, t_settings *s);
void				*routine(void	*philo_data);
void				ft_usleep(long unsigned int time_in_ms, t_philo *philo);
int					philo_take_fork(t_philo *philo);
int					is_philo_alive(t_philo	*philo);
void				death_checker(t_philo **philo, t_settings *s);
long int			get_time2(void);
void				*philo_one(t_philo *philo);

#endif
