/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:06:11 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/27 17:14:15 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_glob_info	*glob_info;
	t_philo		*philo;

	if (ac == 5 || ac == 6)
	{
		glob_info = malloc (sizeof(t_glob_info));
		if (args_check(glob_info, av) == 1)
		{
			printf("invalide arguments !\n");
			return (0);
		}
		allocation_func(glob_info);
		mutex_init_func(glob_info);
		philo = malloc (sizeof(t_philo) * glob_info->num_of_philo);
		variables_initialisation(glob_info, philo);
		threads_creation(philo);
		mutex_destroy_func(glob_info);
		free_func(glob_info);
		free(philo);
	}
	else
		printf("invalide arguments !\n");
	return (0);
}
