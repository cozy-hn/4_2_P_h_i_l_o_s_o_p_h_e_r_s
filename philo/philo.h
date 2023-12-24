/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:12:49 by jiko              #+#    #+#             */
/*   Updated: 2023/12/24 21:38:56 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_arg
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}				t_arg;

typedef struct s_mutex
{
	int				*fork;
	pthread_mutex_t	*fork_mutex;
	int				dead;
	pthread_mutex_t	dead_mutex;
}				t_mutex;

typedef struct s_data
{
	int				left_fork;
	int				right_fork;
	int				start_time;
	int				end_time;
	int				eat_count;
}				t_data;

typedef struct s_philo
{
	int					id;
	t_arg				*arg;
	t_data				*data;
	t_mutex				*mutex;
}				t_philo;

int	ft_atoi(const char *str);
int	ft_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4);

#endif
