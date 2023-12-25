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
	return ((int)result);
}

int	ft_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
	if (ptr1)
		free(ptr1);
	return (1);
}
