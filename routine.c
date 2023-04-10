/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:26:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/09 23:17:49 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->glob_info->print_mutex));
	pthread_mutex_lock(&(philo->glob_info->control_mutex));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->glob_info->control_mutex));
	if (!philo->glob_info->dead_or_not)
		printf("%ld %d is eating\n", get_time() - \
		philo->glob_info->start_time, philo->index + 1);
	pthread_mutex_unlock(&(philo->glob_info->print_mutex));
	while (get_time() - philo->last_eat \
	< (unsigned long)philo->glob_info->time_to_eat \
	&& !philo->glob_info->dead_or_not)
		usleep(200);
}

int	there_is_only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->glob_info->control_mutex));
	if (philo->glob_info->num_of_philo == 1)
	{
		pthread_mutex_unlock(&(philo->glob_info->forks[philo->rfid]));
		pthread_mutex_unlock(&(philo->glob_info->control_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->glob_info->control_mutex));
	return (0);
}

int	philo_went_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->glob_info->print_mutex));
	philo->start_of_sleep = get_time();
	if (!philo->glob_info->dead_or_not)
		printf("%ld %d is sleeping\n", get_time() - \
		philo->glob_info->start_time, philo->index + 1);
	pthread_mutex_unlock(&(philo->glob_info->print_mutex));
	pthread_mutex_lock(&(philo->glob_info->control_mutex));
	if (philo->glob_info->dead_or_not)
	{
		pthread_mutex_unlock(&(philo->glob_info->control_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->glob_info->control_mutex));
	while (get_time() - philo->start_of_sleep \
	< (unsigned long)philo->glob_info->time_to_sleep \
	&& !philo->glob_info->dead_or_not)
		usleep(200);
	return (0);
}

int	forks_and_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->glob_info->forks[philo->rfid]));
	pthread_mutex_lock(&(philo->glob_info->print_mutex));
	if (!philo->glob_info->dead_or_not)
		printf("%ld %d has taken a fork\n", get_time() - \
		philo->glob_info->start_time, philo->index + 1);
	pthread_mutex_unlock(&(philo->glob_info->print_mutex));
	if (there_is_only_one_philo(philo) == 1)
		return (1);
	pthread_mutex_lock(&(philo->glob_info->forks[philo->lfid]));
	pthread_mutex_lock(&(philo->glob_info->print_mutex));
	if (!philo->glob_info->dead_or_not)
		printf("%ld %d has taken a fork\n", get_time() - \
		philo->glob_info->start_time, philo->index + 1);
	pthread_mutex_unlock(&(philo->glob_info->print_mutex));
	philo_is_eating(philo);
	pthread_mutex_lock(&(philo->glob_info->control_mutex));
	philo->glob_info->eat_times[philo->index] += 1;
	pthread_mutex_unlock(&(philo->glob_info->control_mutex));
	pthread_mutex_unlock(&(philo->glob_info->forks[philo->lfid]));
	pthread_mutex_unlock(&(philo->glob_info->forks[philo->rfid]));
	return (0);
}

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	if ((philo->index + 1) % 2 != 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&(philo->glob_info->print_mutex));
		if (!philo->glob_info->dead_or_not)
			printf("%ld %d is thinking\n", get_time() - \
			philo->glob_info->start_time, (philo->index + 1));
		pthread_mutex_unlock(&(philo->glob_info->print_mutex));
		if (forks_and_eating(philo) == 1)
			return (NULL);
		if (philo_went_to_sleep(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
