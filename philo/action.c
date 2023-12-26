/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:16:31 by jiko              #+#    #+#             */
/*   Updated: 2023/12/25 22:44:23 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int state_check(t_philo *philo, t_arg *arg)
{
    struct timeval	time;
    long long		now;

    arg_time_set(&now);
    if (now - philo->last_eat_time > arg->time_to_die)
    {
        arg->dead = 1;
        printf("%lld %d died\n", now - arg->start_time, philo->philo_id);
        return (2);
    }
    return (0);
}

void philo_cycle(t_philo *philo)
{
    pthread_mutex_lock(philo->arg->rsc_mutex);
    while (!philo->arg->dead && !philo->arg->error)
    {
        pthread_mutex_unlock(philo->arg->rsc_mutex);
        hold_forks(philo, philo->philo_id % 2);
        hold_forks(philo, (philo->philo_id + 1) % 2);
        eat(philo);
        release_forks(philo, philo->philo_id % 2);
        release_forks(philo, (philo->philo_id + 1) % 2);
        if (philo->arg->must_eat == philo->eat_count)
        {
            pthread_mutex_lock(philo->arg->rsc_mutex);
            philo->arg->done++;
            break ;
        }
        sleep(philo);
        pthread_mutex_lock(philo->arg->rsc_mutex);
    }
    pthread_mutex_unlock(philo->arg->rsc_mutex);
}

void philo_act(t_philo *philo)
{
    long long		now;

    pthread_mutex_lock(philo->arg->rsc_mutex);
    philo->last_eat_time = philo->arg->start_time;
    pthread_mutex_unlock(philo->arg->rsc_mutex);
    if (philo->philo_id % 2 == 0 || (philo->philo_id == philo->arg->philo_num && philo->philo_id % 2 == 1))
    {
        pthread_mutex_lock(philo->arg->rsc_mutex);
        if (philo->arg->dead == 1)
        {
            pthread_mutex_unlock(philo->arg->rsc_mutex);
            return ;
        }
        printf("%lld %d is thinking\n", arg_time_set(&now) - philo->arg->start_time, philo->philo_id);
        pthread_mutex_unlock(philo->arg->rsc_mutex);
        if (philo->arg->time_to_die > philo->arg->time_to_eat)
            usleep(philo->arg->time_to_eat * 200);
        else
            usleep(philo->arg->time_to_die * 1000);
    }
    philo_cycle(philo);
}