/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:49:39 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/29 08:49:09 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(t_philo *philo)
{
	while (get_time() - philo->start_of_sleep \
	< (unsigned long)philo->glob_info->time_to_sleep)
	{
		usleep(200);
		pthread_mutex_lock(&(philo->glob_info->control_mutex));
		if (philo->glob_info->dead_or_not)
		{
			pthread_mutex_unlock(&(philo->glob_info->control_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->glob_info->control_mutex));
	}
}
