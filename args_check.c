/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:40:36 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/28 17:09:13 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_invalide_input(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	args_check(t_glob_info *glob_info, char **av)
{
	glob_info->num_of_philo = ft_atoi(av[1]);
	glob_info->time_to_die = ft_atoi(av[2]);
	glob_info->time_to_eat = ft_atoi(av[3]);
	glob_info->time_to_sleep = ft_atoi(av[4]);
	if (glob_info->num_of_philo <= 0 || glob_info->time_to_die <= 0 || \
				glob_info->time_to_eat <= 0 || glob_info->time_to_sleep <= 0)
	{
		free(glob_info);
		return (1);
	}
	if (av[5])
	{
		if (check_for_invalide_input(av[5]) == 1)
		{
			free (glob_info);
			return (1);
		}
		glob_info->max_eat_times = ft_atoi(av[5]);
	}
	else
		glob_info->max_eat_times = 0;
	return (0);
}
