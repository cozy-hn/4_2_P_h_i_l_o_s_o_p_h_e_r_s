/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:12:49 by jiko              #+#    #+#             */
/*   Updated: 2023/12/26 23:18:48 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_arg
{
	long long		philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		must_eat;
	long long		start_time;
	long long		must_think;
	int				dead;
	int				error;
	int				done;
	pthread_mutex_t	*start_mutex;
	pthread_mutex_t	*rsc_mutex;
}				t_arg;

typedef struct s_philo
{
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_arg				*arg;
	long long			last_eat_time;
	int					philo_id;
	int					eat_count;
}				t_philo;

int			ft_atoi(const char *str);
long long	time_set(long long *rtn);
void		join_thread(t_philo **philo, int i);
int			free_philo(t_philo **philo, int i, int flag);
int			ft_error(void);
void		philo_act(t_philo *philo);
int			state_check(t_philo **philo, t_arg *arg, int i);
int			print_message(t_philo *philo, char *str);
void		psleep(t_philo *philo);
void		eat(t_philo *philo);
void		hold_forks(t_philo *philo, int right);
void		release_forks(t_philo *philo, int right);

#endif
