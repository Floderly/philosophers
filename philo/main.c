/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/15 23:51:48 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    check_death(s_derly *s_derly)
{
    int i;
    s_derly->count_nb_death = 0;
    while (s_derly->count_nb_death <= s_derly->number_of_philosophers)
    {
        i = 0;
        while (i < s_derly->number_of_philosophers)
        {
            if (s_derly->philo[i].last_eat >= 0)
            {
                if (time_diff(s_derly->philo[i].last_eat, get_time()) > s_derly->time_to_die)
                {
                    s_derly->philo[i].is_dead = 1;
                    s_derly->philo[i].last_eat = -1;
                    s_derly->count_nb_death++;
                    printf("%lld test is_dead : %d du philo %d ===============\n",time_diff(s_derly->first_time, get_time()), s_derly->philo[i].is_dead, i + 1);
                }  
            }
            i++;
        }
    }
    printf("Fin death\n");
}
/*
void    check_death(s_derly *s_derly)
{
    int i;
    s_derly->count_nb_death = 0;
    while (s_derly->count_nb_death == 0)
    {
        i = 0;
        while (i < s_derly->number_of_philosophers)
        {
            if (s_derly->philo[i].last_eat >= 0)
            {
                if (time_diff(s_derly->philo[i].last_eat, get_time()) > s_derly->time_to_die)
                {
                    printf("%lldms  %d is died\n",time_diff(s_derly->first_time, get_time()), i + 1);
                    while (i < s_derly->number_of_philosophers)
                    {
                        s_derly->philo[i].is_dead = 1;
                        s_derly->philo[i].last_eat = -1;
                        i++;
                    }
                    s_derly->count_nb_death++;
                }  
            }
            i++;
        }
    }
    printf("Fin death\n");
}*/

// Fonction du thread
void *test1(void *arg)
{
    s_philo *philo;
    s_derly *s_derly;

    philo = (s_philo *)arg;
    s_derly = philo->s_derly;

    while (1)
    {
        if (philo->nb_eat == s_derly->number_of_times_each_philosophers_must_eat)
            break;
        if (philo->is_dead == 1)
            break;
        printf("%lldms - %d is thinking\n", time_diff(s_derly->first_time, get_time()), philo->id_philo);
        pthread_mutex_lock(&philo->l_f);
        printf("%lldms - %d has takem a fork\n", time_diff(s_derly->first_time, get_time()), philo->id_philo);
        if (philo->is_dead == 1)
            break;
        pthread_mutex_lock(philo->r_f);
        printf("%lldms - %d has takem a fork\n", time_diff(s_derly->first_time, get_time()), philo->id_philo);
        printf("%lldms - %d is eating\n", time_diff(s_derly->first_time, get_time()), philo->id_philo);
        usleep(s_derly->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->l_f);
        pthread_mutex_unlock(philo->r_f);
        if (philo->is_dead == 1)
            break;
        philo->last_eat = get_time();
        philo->fin_eat = time_diff(s_derly->first_time, get_time()) * 1000;
        philo->nb_eat++;
        if (philo->is_dead == 1)
            break;
        printf("%lldms - %d is sleeping\n", time_diff(s_derly->first_time, get_time()), philo->id_philo);
        usleep(s_derly->time_to_sleep * 1000);
    }
    printf("Fin du philosophe %d\n", philo->id_philo);
    return (0);
}
void    init_thread(s_derly *s_derly)
{
    int i;

    i = 0;
	s_derly->first_time = get_time();
    while (i < s_derly->number_of_philosophers)
    {
        s_derly->philo[i].s_derly = s_derly;
        printf("Creation thread n%d.\n", i + 1);
        pthread_create(&s_derly->philo[i].t, 0, &test1, &s_derly->philo[i]);
        i++;
    }
    check_death(s_derly);

	i = 0;
	while (i < s_derly->number_of_philosophers)
	{
		pthread_join(s_derly->philo[i].t, 0);
		i++;
	}
}


void	init_philo(s_derly *s_derly)
{
    int i;

    i = 0;
    while (i < s_derly->number_of_philosophers)
    {
        s_derly->philo[i].s_derly = s_derly;
        s_derly->philo[i].id_philo = i + 1;
        s_derly->philo[i].nb_eat = 0;
        s_derly->philo[i].is_dead = 0;
        s_derly->philo[i].last_eat = s_derly->first_time;
        pthread_mutex_init(&s_derly->philo[i].l_f, 0);
        if (i == s_derly->number_of_philosophers - 1)
            s_derly->philo[i].r_f = &s_derly->philo[0].l_f;
        else
            s_derly->philo[i].r_f = &s_derly->philo[i + 1].l_f;
        i++;
    }
}

void	init_data(s_derly *s_derly, int argc, char const *argv[])
{
    s_derly->number_of_philosophers = ft_atoi(argv[1]);
    s_derly->time_to_die = ft_atoi(argv[2]);
    s_derly->time_to_eat = ft_atoi(argv[3]);
    s_derly->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        s_derly->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
    else
        s_derly->number_of_times_each_philosophers_must_eat = -1;
    s_derly->philo = malloc(sizeof(s_derly) * 201);

    init_philo(s_derly);
}


int main(int argc, char const *argv[])
{
    s_derly s_derly;
    if (argc != 5 && argc != 6)
    {
        printf("Besoin de 4 ou 5 arguments\n");
        return (0);
    }

    if (ft_atoi(argv[1]) < 1)
    {
        printf("Argument 1 doit être supérieur à 0\n");
        return (0);
    }
    if (argc == 6 && ft_atoi(argv[5]) < 1)
        return (0);

    printf("Entrer init data.\n");
    init_data(&s_derly, argc , argv);
    printf("Sorti init data et entrer init thread.\n");
    init_thread(&s_derly);

    printf("Tous les threads ont terminé.\n");
    return (0);
}
