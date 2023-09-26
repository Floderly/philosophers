/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/24 21:03:06 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thread_philo_eating_2(t_derly	*t_derly, t_philo *philo)
{
	pthread_mutex_lock(&t_derly->is_dead_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&t_derly->is_dead_last_eat);
	pthread_mutex_lock(&t_derly->nb_eat_each);
	philo->nb_eat++;
	pthread_mutex_unlock(&t_derly->nb_eat_each);
}

int	thread_philo_eating(t_derly	*t_derly, t_philo *philo)
{
	pthread_mutex_lock(&philo->l_f);
	if (check_if_dead(philo, t_derly, 1) == 1)
		return (1);
	pthread_mutex_lock(&t_derly->first_time_m);
	printf("%lldms - %d has taken a fork\n",
		time_diff(t_derly->first_time, get_time()), philo->id_philo);
	pthread_mutex_unlock(&t_derly->first_time_m);
	pthread_mutex_lock(philo->r_f);
	if (check_if_dead(philo, t_derly, 2) == 1)
		return (1);
	pthread_mutex_lock(&t_derly->first_time_m);
	printf("%lldms - %d has taken a fork\n",
		time_diff(t_derly->first_time, get_time()), philo->id_philo);
	printf("%lldms - %d is eating\n",
		time_diff(t_derly->first_time, get_time()), philo->id_philo);
	pthread_mutex_unlock(&t_derly->first_time_m);
	usleep(t_derly->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_f);
	pthread_mutex_unlock(philo->r_f);
	if (check_if_dead(philo, t_derly, 0) == 1)
		return (1);
	thread_philo_eating_2(t_derly, philo);
	return (0);
}

int	thread_philo_p1(t_derly	*t_derly, t_philo *philo)
{
	pthread_mutex_unlock(&t_derly->nb_eat_each);
	pthread_mutex_unlock(&t_derly->nb_philo);
	if (check_if_dead(philo, t_derly, 0) == 1)
		return (1);
	pthread_mutex_lock(&t_derly->first_time_m);
	printf("%lldms - %d is thinking\n",
		time_diff(t_derly->first_time, get_time()), philo->id_philo);
	pthread_mutex_unlock(&t_derly->first_time_m);
	return (0);
}

int	thread_philo_p3(t_derly	*t_derly, t_philo *philo)
{
	if (check_if_dead(philo, t_derly, 0) == 1)
		return (1);
	pthread_mutex_lock(&t_derly->first_time_m);
	printf("%lldms - %d is sleeping\n",
		time_diff(t_derly->first_time, get_time()), philo->id_philo);
	pthread_mutex_unlock(&t_derly->first_time_m);
	usleep(t_derly->time_to_sleep * 1000);
	return (0);
}

void	*thread_philo(void *arg)
{
	t_philo	*philo;
	t_derly	*t_derly;

	philo = (t_philo *)arg;
	t_derly = philo->t_derly;
	if (philo->id_philo % 2 == 0)
		usleep(2500);
	while (1)
	{
		pthread_mutex_lock(&t_derly->nb_philo);
		pthread_mutex_lock(&t_derly->nb_eat_each);
		if (t_derly->number_of_philosophers == 1
			|| philo->nb_eat == t_derly->nb_times_must_eat)
		{
			pthread_mutex_unlock(&t_derly->nb_philo);
			pthread_mutex_unlock(&t_derly->nb_eat_each);
			break ;
		}
		if (thread_philo_p1(t_derly, philo) == 1
			|| thread_philo_eating(t_derly, philo) == 1
			|| thread_philo_p3(t_derly, philo) == 1)
			break ;
	}
	return (0);
}
