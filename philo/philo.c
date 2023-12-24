/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:16:31 by jiko              #+#    #+#             */
/*   Updated: 2023/12/24 22:13:16 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_parse(t_arg *arg, int ac, char **av)
{
	arg->philo_num = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must_eat = ft_atoi(av[5]);
	else
		arg->must_eat = -1;
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1
		|| arg->time_to_sleep < 1 || arg->must_eat < 1)
		return (ft_free(arg, NULL, NULL, NULL));
	return (0);
}

static int	set_mutex(t_mutex **mutex, t_arg *arg, int *i)
{
	*mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (!*mutex)
		return (1);
	(*mutex)->dead = 0;
	if (pthread_mutex_init(&(*mutex)->dead_mutex, NULL) != 0)
		return (ft_free(*mutex, arg, NULL, NULL));
	(*mutex)->fork = (int *)malloc(sizeof(int) * arg->philo_num);
	if (!(*mutex)->fork)
	{
		pthread_mutex_destroy(&(*mutex)->dead_mutex);
		return (ft_free(*mutex, arg, NULL, NULL));
	}
	(*mutex)->fork_mutex = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(*mutex)->fork_mutex)
	{
		pthread_mutex_destroy(&(*mutex)->dead_mutex);
		return (ft_free(*mutex, arg, (*mutex)->fork, NULL));
	}
	while ((*i)++ < arg->philo_num)
	{
		(*mutex)->fork[(*i)] = 1;
		if (pthread_mutex_init(&(*mutex)->fork_mutex[(*i)], NULL) != 0)
		{
			pthread_mutex_destroy(&(*mutex)->dead_mutex);
			while (--(*i) >= 0)
				pthread_mutex_destroy(&(*mutex)->fork_mutex[(*i)]);
			return (ft_free(*mutex, arg, (*mutex)->fork, (*mutex)->fork_mutex));
		}
	}
	return (0);
}

static int	set_philo(t_philo *philo, t_arg *arg, t_mutex *mutex, int *idx)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].arg = arg;
		philo[i].data = (t_data *)malloc(sizeof(t_data));
		if (!philo[i].data)
		{
			while (--i >= 0)
				free(philo[i].data);
			pthread_mutex_destroy(&mutex->dead_mutex);
			while (--(*idx) >= 0)
				pthread_mutex_destroy(&mutex->fork_mutex[(*idx)]);
			return (ft_free(mutex, arg, mutex->fork, mutex->fork_mutex));
		}
	}
	return (0);
}

static int	philo_init(t_philo **philo, int ac, char **av)
{
	t_arg	*arg;
	t_mutex	*mutex;
	int		idx;

	idx = 0;
	if (ac != 5 && ac != 6)
		return (1);
	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (1);
	if (arg_parse(arg, ac, av) == 1)
		return (1);
	if (set_mutex(&mutex, arg, &idx) == 1)
		return (1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * arg->philo_num);
	{
		pthread_mutex_destroy(&mutex->dead_mutex);
		while (--idx >= 0)
			pthread_mutex_destroy(&mutex->fork_mutex[idx]);
		return (ft_free(mutex, arg, mutex->fork, mutex->fork_mutex));
	}
	if (set_philo(*philo, arg, mutex, &idx) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*thread;
	t_philo		*philo;

	if (philo_init(&philo, ac, av) == 1)
		return (1);
	
	return (0);
}
