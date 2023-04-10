/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:31:07 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/09 23:07:05 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_or_not(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->glob_info->num_of_philo)
	{
		pthread_mutex_lock(&philo->glob_info->control_mutex);
		if ((get_time() - philo[i].last_eat) >= \
		(unsigned long)philo->glob_info->time_to_die \
		&& !philo->glob_info->philos_are_full)
		{
			pthread_mutex_lock(&philo->glob_info->print_mutex);
			philo->glob_info->dead_or_not = 1;
			printf("%ld %d died\n", (get_time() - \
			philo->glob_info->start_time), i + 1);
			pthread_mutex_unlock(&philo->glob_info->print_mutex);
			pthread_mutex_unlock(&philo->glob_info->control_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->glob_info->control_mutex);
		i++;
	}
	return (0);
}

int	check_for_death_and_full_philos(t_philo *philo)
{
	while (!philo->glob_info->dead_or_not && !philo->glob_info->philos_are_full)
	{
		if (dead_or_not(philo) == 1)
			return (1);
		pthread_mutex_lock(&philo->glob_info->control_mutex);
		if (check_eat_times(philo) == 1)
		{
			philo->glob_info->dead_or_not = 1;
			pthread_mutex_unlock(&philo->glob_info->control_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->glob_info->control_mutex);
	}
	return (0);
}
