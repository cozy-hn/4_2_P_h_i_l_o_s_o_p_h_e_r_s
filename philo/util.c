/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:22:09 by jiko              #+#    #+#             */
/*   Updated: 2023/12/24 21:38:35 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && i < 13)
			result = result * 10 + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	if (result > 2147483647 || result < 0)
		return (-1);
	return (result);
}

long long arg_time_set(long long *rtn)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	*rtn = ((long long)time.tv_sec * 1000LL) + ((long long)time.tv_usec / 1000LL);
	return (*rtn);
}

void join_thread(t_philo **philo, int i)
{
	while (--i > 0)
		pthread_join((*philo)[i].thread_id, NULL);
}

int free_philo(t_philo **philo, int i, int flag)
{

	if (flag == 2)
		free((*philo)[i].right_fork);
	while (--i > 0)
	{
		if (flag >= 1)
			pthread_mutex_destroy((*philo)[i].right_fork);
		free((*philo)[i].right_fork);
	}
	free(*philo);
	return (1);
}	

int ft_error(void)
{
	printf("Error\n");
	return (1);
}
