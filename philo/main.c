/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:20:01 by fderly            #+#    #+#             */
/*   Updated: 2023/09/04 23:23:43 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char const *argv[])
{
    s_derly s_derly;
    if (argc != 5 && argc != 6)
        return (0);

    if (ft_atoi(argv[1]) < 1)
        return (0);

    s_derly.number_of_philophers = ft_atoi(argv[1]);
    s_derly.time_to_die = ft_atoi(argv[2]);
    s_derly.time_to_eat = ft_atoi(argv[3]);
    s_derly.time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        s_derly.number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
    else
        s_derly.number_of_times_each_philosophers_must_eat = -1;
    return 0;
}