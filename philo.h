/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:06:15 by aouchaad          #+#    #+#             */
/*   Updated: 2023/04/09 23:12:40 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_glob_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	control_mutex;
	pthread_mutex_t	print_mutex;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				max_eat_times;
	int				time_to_sleep;
	int				dead_or_not;
	int				*eat_times;
	unsigned long	*start_of_thinking;
	unsigned long	start_time;
	int				philos_are_full;
}	t_glob_info;

typedef struct s_philo
{
	t_glob_info		*glob_info;
	pthread_t		threads;
	int				index;
	unsigned long	last_eat;
	unsigned long	start_of_sleep;
	int				lfid;
	int				rfid;
}	t_philo;

unsigned long	get_time(void);
int				ft_atoi(char *string);
int				threads_creation(t_philo *philo);
int				args_check(t_glob_info *glob_info, char **av);
int				dead_or_not(t_philo *philo);
int				check_eat_times(t_philo *philo);
int				there_is_only_one_philo(t_philo *philo);
int				check_for_death_and_full_philos(t_philo *philo);
int				philo_went_to_sleep(t_philo *philo);
int				forks_and_eating(t_philo *philo);
void			allocation_func(t_glob_info *glob_info);
void			free_func(t_glob_info *glob_info);
void			philo_is_eating(t_philo *philo);
void			*routine(void *x);
void			mutex_init_func(t_glob_info *glob_info);
void			mutex_destroy_func(t_glob_info *glob_info);
void			variables_initialisation(t_glob_info *glob_info, \
t_philo *philo);

#endif