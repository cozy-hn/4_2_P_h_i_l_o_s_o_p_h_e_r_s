/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:01:43 by jiko              #+#    #+#             */
/*   Updated: 2023/12/27 17:37:33 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	checker(t_arg *arg, long long limit, long long time, int sleep_time)
{
	pthread_mutex_lock(arg->rsc_mutex);
	while ((!arg->dead && !arg->error) && time < limit)
	{
		pthread_mutex_unlock(arg->rsc_mutex);
		usleep(sleep_time / 2 + 1);
		time_set(&time);
		pthread_mutex_lock(arg->rsc_mutex);
	}
	pthread_mutex_unlock(arg->rsc_mutex);
}

void	psleep(t_philo *philo)
{
	long long		now;
	long long		limit;

	pthread_mutex_lock(philo->arg->rsc_mutex);
	time_set(&now);
	if (print_message(philo, "is sleeping") == 0)
	{
		pthread_mutex_unlock(philo->arg->rsc_mutex);
		limit = now + philo->arg->time_to_sleep;
		checker(philo->arg, limit, now, philo->arg->time_to_sleep);
		pthread_mutex_lock(philo->arg->rsc_mutex);
		time_set(&now);
		print_message(philo, "is thinking");
		pthread_mutex_unlock(philo->arg->rsc_mutex);
		if (philo->arg->must_think >= 0 && philo->arg->philo_num % 2 == 1)
		{
			limit = now + philo->arg->must_think;
			checker(philo->arg, limit, now, philo->arg->time_to_sleep);
			usleep(100);
		}
	}
	else
		pthread_mutex_unlock(philo->arg->rsc_mutex);
}

void	eat(t_philo *philo)
{
	long long		now;
	long long		limit;

	pthread_mutex_lock(philo->arg->rsc_mutex);
	time_set(&now);
	if (print_message(philo, "is eating") == 0)
	{
		philo->last_eat_time = now;
		pthread_mutex_unlock(philo->arg->rsc_mutex);
		limit = now + philo->arg->time_to_eat;
		checker(philo->arg, limit, now, philo->arg->philo_num);
		philo->eat_count++;
	}
	else
		pthread_mutex_unlock(philo->arg->rsc_mutex);
}

void	hold_forks(t_philo *philo, int right)
{
	if (right == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->arg->rsc_mutex);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->arg->rsc_mutex);
		print_message(philo, "has taken a fork");
	}
	pthread_mutex_unlock(philo->arg->rsc_mutex);
}

void	release_forks(t_philo *philo, int right)
{
	if (right == 1)
		pthread_mutex_unlock(philo->right_fork);
	else
		pthread_mutex_unlock(philo->left_fork);
}
