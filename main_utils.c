/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:23:20 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/09 23:09:54 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	variables_initialisation(t_glob_info *glob_info, t_philo *philo)
{
	int	i;

	i = 0;
	glob_info->dead_or_not = 0;
	glob_info->philos_are_full = 0;
	while (i < glob_info->num_of_philo)
	{
		philo[i].index = i;
		philo[i].lfid = (i + (glob_info->num_of_philo - 1)) \
		% glob_info->num_of_philo;
		philo[i].rfid = i;
		philo[i].glob_info = glob_info;
		glob_info->eat_times[i] = 0;
		i++;
	}
}

void	allocation_func(t_glob_info *glob_info)
{
	glob_info->forks = malloc (sizeof(pthread_mutex_t) \
	* glob_info->num_of_philo);
	glob_info->eat_times = malloc (sizeof(int *) * glob_info->num_of_philo);
	glob_info->start_of_thinking = malloc(sizeof(int *) \
	* glob_info->num_of_philo);
}

void	free_func(t_glob_info *glob_info)
{
	free(glob_info->forks);
	free(glob_info->eat_times);
	free(glob_info->start_of_thinking);
	free(glob_info);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	check_eat_times(t_philo *philo)
{
	int	i;
	int	count;

	if (philo->glob_info->max_eat_times != 0)
	{
		if (philo->glob_info->eat_times[0] >= philo->glob_info->max_eat_times)
		{
			i = 1;
			count = 1;
			while (philo->glob_info->eat_times[i] \
			>= philo->glob_info->max_eat_times)
			{
				count++;
				i++;
			}
			if (count == philo->glob_info->num_of_philo)
			{
				philo->glob_info->philos_are_full = 1;
				return (1);
			}
		}
	}
	return (0);
}
