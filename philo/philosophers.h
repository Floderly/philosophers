/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:03:46 by fderly            #+#    #+#             */
/*   Updated: 2023/09/07 17:35:26 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

struct t_derly;

typedef struct t_philo
{
    int id_philo;
    int nb_eat;
    int is_dead;
    long long   last_eat;
    long long   fin_eat;
	pthread_t		t;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
    struct t_derly *s_derly;
}	s_philo;

typedef struct t_derly
{
	int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosophers_must_eat;
    int count_nb_death;
    long long   first_time;
    s_philo *philo;

}	s_derly;

int	ft_atoi(const char *str);
unsigned long	get_time(void);
long long	time_diff(long long i, long long time);

#endif
