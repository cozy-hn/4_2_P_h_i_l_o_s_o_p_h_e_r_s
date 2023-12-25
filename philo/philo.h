/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:12:49 by jiko              #+#    #+#             */
/*   Updated: 2023/12/25 22:42:30 by jiko             ###   ########.fr       */
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
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				must_think;
	int				must_eat;
	int				dead;
	pthread_mutex_t	*start_mutex;
	pthread_mutex_t	*rsc_mutex;
}				t_arg;

typedef struct s_philo
{
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_arg				*arg;
	int					end_time;
	int					philo_id;
	int					eat_count;
}				t_philo;

int	ft_atoi(const char *str);
int	ft_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4);

#endif
