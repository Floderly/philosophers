/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:03:46 by fderly            #+#    #+#             */
/*   Updated: 2023/09/24 20:57:09 by fderly           ###   ########.fr       */
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

struct	s_derly;

typedef struct s_philo
{
	int				id_philo;
	int				nb_eat;
	int				is_dead;
	long long		last_eat;
	long long		fin_eat;
	pthread_t		t;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
	pthread_mutex_t	nb_eat_philo;
	struct s_derly	*t_derly;
}	t_philo;

typedef struct s_derly
{
	pthread_mutex_t	nb_philo;
	pthread_mutex_t	first_time_m;
	pthread_mutex_t	is_dead_last_eat;
	pthread_mutex_t	nb_eat_each;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_must_eat;
	int				count_nb_death;
	long long		first_time;
	t_philo			*philo;

}	t_derly;

int				ft_atoi(const char *str);
unsigned long	get_time(void);
long long		time_diff(long long i, long long time);
void			check_death(t_derly *t_derly);
void			*thread_philo(void *arg);
void			pthread_join_yes(t_derly *t_derly);
int				check_if_dead(t_philo *philo, t_derly *t_derly, int fork_lock);

#endif
