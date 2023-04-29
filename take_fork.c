/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:29:14 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/29 08:48:59 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (!philo->glob_info->dead_or_not)
	{
		pthread_mutex_lock(&(philo->glob_info->print_mutex));
		printf("%ld %d has taken a fork\n", get_time() - \
		philo->glob_info->start_time, philo->index + 1);
		pthread_mutex_unlock(&(philo->glob_info->print_mutex));
	}
}
