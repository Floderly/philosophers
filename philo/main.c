/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/24 20:56:13 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pthread_join_yes(t_derly *t_derly)
{
	int	i;

	i = 0;
	while (i < t_derly->number_of_philosophers)
	{
		pthread_join(t_derly->philo[i].t, 0);
		i++;
	}
	pthread_mutex_destroy(&t_derly->nb_philo);
	pthread_mutex_destroy(&t_derly->first_time_m);
	pthread_mutex_destroy(&t_derly->is_dead_last_eat);
	pthread_mutex_destroy(&t_derly->nb_eat_each);
	i = 0;
	while (i < t_derly->number_of_philosophers)
	{
		pthread_mutex_destroy(&t_derly->philo[i].l_f);
		i++;
	}
	free(t_derly->philo);
}

void	init_thread(t_derly *t_derly)
{
	int	i;

	i = 0;
	while (i < t_derly->number_of_philosophers)
	{
		t_derly->philo[i].t_derly = t_derly;
		pthread_create(&t_derly->philo[i].t, 0, &thread_philo,
			&t_derly->philo[i]);
		i++;
	}
	check_death(t_derly);
}

void	init_philo(t_derly *t_derly)
{
	int	i;

	i = 0;
	while (i < t_derly->number_of_philosophers)
	{
		t_derly->philo[i].t_derly = t_derly;
		t_derly->philo[i].id_philo = i + 1;
		t_derly->philo[i].nb_eat = 0;
		t_derly->philo[i].is_dead = 0;
		t_derly->philo[i].last_eat = t_derly->first_time;
		pthread_mutex_init(&t_derly->philo[i].l_f, 0);
		if (i == t_derly->number_of_philosophers - 1)
			t_derly->philo[i].r_f = &t_derly->philo[0].l_f;
		else
			t_derly->philo[i].r_f = &t_derly->philo[i + 1].l_f;
		i++;
	}
	pthread_mutex_init(&t_derly->nb_philo, 0);
	pthread_mutex_init(&t_derly->first_time_m, 0);
	pthread_mutex_init(&t_derly->is_dead_last_eat, 0);
	pthread_mutex_init(&t_derly->nb_eat_each, 0);
}

void	init_data(t_derly *t_derly, int argc, char const *argv[])
{
	t_derly->number_of_philosophers = ft_atoi(argv[1]);
	t_derly->time_to_die = ft_atoi(argv[2]);
	t_derly->time_to_eat = ft_atoi(argv[3]);
	t_derly->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		t_derly->nb_times_must_eat = ft_atoi(argv[5]);
	else
		t_derly->nb_times_must_eat = -1;
	t_derly->philo = malloc(sizeof(t_philo) * 201);
	t_derly->first_time = get_time();
	init_philo(t_derly);
}

int	main(int argc, char const *argv[])
{
	t_derly	t_derly;

	if (argc != 5 && argc != 6)
	{
		printf("Besoin de 4 ou 5 arguments\n");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Nombre de philo doit etre entre 1 et 200\n");
		return (2);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (3);
	if (ft_atoi(argv[2]) < 1 || (argv[2][0] >= 'A' && (argv[2][0] >= 'z'))
	|| ft_atoi(argv[3]) < 1 || (argv[3][0] >= 'A' && (argv[3][0] >= 'z'))
	|| ft_atoi(argv[4]) < 1 || (argv[4][0] >= 'A' && (argv[4][0] >= 'z')))
	{
		printf("Nombre uniquement et postif\n");
		return (4);
	}
	init_data(&t_derly, argc, argv);
	init_thread(&t_derly);
	return (0);
}
