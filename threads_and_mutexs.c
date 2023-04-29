/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutexs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:29:21 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/28 09:28:12 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init_func(t_glob_info *glob_info)
{
	int	i;

	i = 0;
	while (i < glob_info->num_of_philo)
	{
		pthread_mutex_init(&(glob_info->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(glob_info->control_mutex), NULL);
	pthread_mutex_init(&(glob_info->print_mutex), NULL);
}

void	mutex_destroy_func(t_glob_info *glob_info)
{
	int	i;

	i = 0;
	while (i < glob_info->num_of_philo)
	{
		pthread_mutex_destroy(&(glob_info->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(glob_info->control_mutex));
	pthread_mutex_destroy(&(glob_info->print_mutex));
}

int	threads_creation(t_philo *philo)
{
	int	i;

	i = 0;
	philo->glob_info->start_time = get_time();
	while (i < philo->glob_info->num_of_philo)
	{
		philo[i].last_eat = get_time();
		pthread_create((&(philo[i].threads)), NULL, routine, &(philo[i]));
		usleep(10);
		i++;
	}
	i = 0;
	check_for_death_and_full_philos(philo);
	while (i < philo->glob_info->num_of_philo)
	{
		pthread_join((philo[i].threads), NULL);
		i++;
	}
	return (1);
}
