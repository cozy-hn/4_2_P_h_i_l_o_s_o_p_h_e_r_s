/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:40:11 by jiko              #+#    #+#             */
/*   Updated: 2023/12/26 23:19:46 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state_check(t_philo **philo, t_arg *arg, int i)
{
	struct timeval	time;
	long long		now;

	if (arg->error == 1)
	{
		pthread_mutex_unlock(arg->rsc_mutex);
		join_thread(philo, arg->philo_num + 1);
		free_philo(philo, arg->philo_num + 1, 1);
		return (1);
	}
	time_set(&now);
	if (now - (*philo)[i].last_eat_time > arg->time_to_die)
	{
		arg->dead = 1;
		printf("%lld %d died\n", now - arg->start_time, (*philo)[i].philo_id);
		return (2);
	}
	return (0);
}

int	print_message(t_philo *philo, char *str)
{
	long long		now;

	if (philo->arg->dead == 1 || philo->arg->error == 1)
		return (1);
	time_set(&now);
	printf("%lld %d %s\n", now - philo->arg->start_time, philo->philo_id, str);
	return (0);
}
