/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/24 20:02:36 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat(t_derly *t_derly)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&t_derly->nb_philo);
	while (i < t_derly->number_of_philosophers)
	{
		pthread_mutex_unlock(&t_derly->nb_philo);
		pthread_mutex_lock(&t_derly->nb_eat_each);
		if (t_derly->philo[i].nb_eat
			!= t_derly->nb_times_must_eat)
		{
			pthread_mutex_unlock(&t_derly->nb_eat_each);
			return (0);
		}
		pthread_mutex_unlock(&t_derly->nb_eat_each);
		i++;
		pthread_mutex_lock(&t_derly->nb_philo);
	}
	pthread_mutex_unlock(&t_derly->nb_philo);
	return (1);
}

void	set_all_dead(t_derly *t_derly)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&t_derly->nb_philo);
	while (j < t_derly->number_of_philosophers)
	{
		pthread_mutex_unlock(&t_derly->nb_philo);
		pthread_mutex_lock(&t_derly->is_dead_last_eat);
		t_derly->philo[j].is_dead = 1;
		t_derly->philo[j].last_eat = -1;
		pthread_mutex_unlock(&t_derly->is_dead_last_eat);
		j++;
		pthread_mutex_lock(&t_derly->nb_philo);
	}
	pthread_mutex_unlock(&t_derly->nb_philo);
}

void	check_time_death(t_derly *t_derly, int i)
{
	if (time_diff(t_derly->philo[i].last_eat, get_time())
		> t_derly->time_to_die)
	{
		pthread_mutex_unlock(&t_derly->is_dead_last_eat);
		pthread_mutex_lock(&t_derly->first_time_m);
		printf("%lldms %d is died\n", time_diff(t_derly->first_time,
				get_time()), i + 1);
		pthread_mutex_unlock(&t_derly->first_time_m);
		set_all_dead(t_derly);
		pthread_join_yes(t_derly);
		exit(0);
	}
	else
		pthread_mutex_unlock(&t_derly->is_dead_last_eat);
}

void	check_death(t_derly *t_derly)
{
	int	i;

	while (check_eat(t_derly) == 0)
	{
		i = 0;
		pthread_mutex_lock(&t_derly->nb_philo);
		while (i < t_derly->number_of_philosophers)
		{
			pthread_mutex_unlock(&t_derly->nb_philo);
			pthread_mutex_lock(&t_derly->is_dead_last_eat);
			if (t_derly->philo[i].last_eat >= 0)
			{
				check_time_death(t_derly, i);
			}
			else
				pthread_mutex_unlock(&t_derly->is_dead_last_eat);
			i++;
			pthread_mutex_lock(&t_derly->nb_philo);
		}
		pthread_mutex_unlock(&t_derly->nb_philo);
	}
	set_all_dead(t_derly);
}
