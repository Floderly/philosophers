/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:38:30 by fderly            #+#    #+#             */
/*   Updated: 2023/09/06 21:07:13 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	time_diff(long long i, long long time)
{
	return (time - i);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}


/*
void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat);
	philo->time_eat = get_time();
	pthread_mutex_unlock(&philo->data->eat);
}*/
/*
void	ft_usleep(int ms, t_data *data)
{
	long int	time;

	(void) data;
	time = get_time();
	while (42)
	{
		if (time_diff(time, get_time()) >= ms)
		{
			break ;
		}
		usleep(50);
	}
}*/
