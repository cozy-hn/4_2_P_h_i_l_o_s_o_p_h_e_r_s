/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:16:31 by jiko              #+#    #+#             */
/*   Updated: 2023/12/28 17:31:20 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_init(t_arg *arg, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	arg->philo_num = ft_atoll(av[1]);
	arg->time_to_die = ft_atoll(av[2]);
	arg->time_to_eat = ft_atoll(av[3]);
	arg->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		arg->must_eat = ft_atoll(av[5]);
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1
		|| arg->time_to_sleep < 1 || (ac == 6 && arg->must_eat < 1))
		return (1);
	arg->must_think = arg->time_to_eat - arg->time_to_sleep;
	return (0);
}

static int	philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * (arg->philo_num + 1));
	if (!*philo)
		return (1);
	memset(*philo, 0, sizeof(t_philo) * (arg->philo_num + 1));
	while (++i <= arg->philo_num)
	{
		(*philo)[i].philo_id = i;
		(*philo)[i].arg = arg;
		(*philo)[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (!(*philo)[i].right_fork)
			return (free_philo(philo, i, 0));
		if (pthread_mutex_init((*philo)[i].right_fork, NULL) != 0)
			return (free_philo(philo, i, 2));
	}
	(*philo)[1].left_fork = (*philo)[arg->philo_num].right_fork;
	i = 1;
	while (++i <= arg->philo_num)
		(*philo)[i].left_fork = (*philo)[i - 1].right_fork;
	return (0);
}

static int	thread_init(t_philo **philo, t_arg *arg)
{
	int	i;

	pthread_mutex_lock(arg->start_mutex);
	i = 0;
	while (++i <= arg->philo_num)
	{
		if (pthread_create(&(*philo)[i].thread_id, NULL,
			(void *)philo_act, &(*philo)[i]) != 0)
		{
			pthread_mutex_unlock(arg->start_mutex);
			arg->error = 1;
			join_thread(philo, i);
			return (free_philo(philo, arg->philo_num + 1, 1));
		}
	}
	time_set(&arg->start_time);
	pthread_mutex_unlock(arg->start_mutex);
	return (0);
}

static int	monitoring(t_philo **philo, t_arg *arg)
{
	int	i;
	int	state;

	while (42)
	{
		i = 0;
		while (++i <= arg->philo_num)
		{
			pthread_mutex_lock(arg->rsc_mutex);
			if ((*philo)[i].last_eat_time != 0)
			{
				state = state_check(philo, arg, i);
				if (state == 1)
					return (1);
				else if (state == 2)
					return (pthread_mutex_unlock(arg->rsc_mutex));
			}
			pthread_mutex_unlock(arg->rsc_mutex);
		}
		pthread_mutex_lock(arg->rsc_mutex);
		if (arg->done == arg->philo_num)
			return (pthread_mutex_unlock(arg->rsc_mutex));
		pthread_mutex_unlock(arg->rsc_mutex);
	}
}

int	main(int ac, char **av)
{
	static pthread_mutex_t	start_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_mutex_t	rsc_mutex = PTHREAD_MUTEX_INITIALIZER;
	t_philo					*philo;
	t_arg					arg;

	memset(&arg, 0, sizeof(t_arg));
	arg.start_mutex = &start_mutex;
	arg.rsc_mutex = &rsc_mutex;
	if (arg_init(&arg, ac, av) == 1 || philo_init(&philo, &arg) == 1
		|| thread_init(&philo, &arg) == 1 || monitoring(&philo, &arg) == 1)
		return (ft_error());
	join_thread(&philo, arg.philo_num + 1);
	free_philo(&philo, arg.philo_num + 1, 1);
	return (0);
}
