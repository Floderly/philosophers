/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/24 20:56:51 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_dead(t_philo *philo, t_derly *t_derly, int fork_lock)
{
	pthread_mutex_lock(&t_derly->is_dead_last_eat);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(&t_derly->is_dead_last_eat);
		if (fork_lock == 1)
		{
			pthread_mutex_unlock(&philo->l_f);
		}
		if (fork_lock == 2)
		{
			pthread_mutex_unlock(&philo->l_f);
			pthread_mutex_unlock(philo->r_f);
		}
		return (1);
	}
	pthread_mutex_unlock(&t_derly->is_dead_last_eat);
	return (0);
}
