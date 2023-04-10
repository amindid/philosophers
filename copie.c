#include "philo.h"

//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

int	check_eat_times(t_philo *philo)
{
	int	i;
	int	count;

	if (philo->glob_info->max_eat_times != 0)
	{
		philo->glob_info->eat_times[philo->index] += 1;
		if (philo->glob_info->eat_times[0] >= philo->glob_info->max_eat_times)
		{
			i = 1;
			count = 1;
			while (philo->glob_info->eat_times[i] == philo->glob_info->max_eat_times)
			{
				count++;
				i++;
			}
			if (count == philo->glob_info->num_of_philo)
				return 1;
		}
	}
	return 0;
}

unsigned long get_time(void)
{
	struct timeval tv;
	unsigned long time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	*routine(void *x)
{
	t_philo *philo;
	philo = (t_philo *)x;
	
	if ((philo->index + 1) % 2 != 0)
		usleep(200);
	
	while (1)
	{
		pthread_mutex_lock(&(philo->glob_info->print));
		if (!philo->glob_info->should_die)
		{	
			printf("%ld %d is thinking\n", get_time() - philo->glob_info->start_time, (philo->index + 1));
		}
		pthread_mutex_unlock(&(philo->glob_info->print));
		pthread_mutex_lock(&(philo->glob_info->forks[philo->rfid]));
		pthread_mutex_lock(&(philo->glob_info->print));
		if (!philo->glob_info->should_die)
		{	
			printf("%ld %d has taken a fork\n", get_time() - philo->glob_info->start_time, philo->index + 1);
		}
		pthread_mutex_unlock(&(philo->glob_info->print));
		pthread_mutex_lock(&(philo->glob_info->forks[philo->lfid]));
		
		pthread_mutex_lock(&(philo->glob_info->print));
		if (!philo->glob_info->should_die)
		{	
			printf("%ld %d has taken a fork\n", get_time() - philo->glob_info->start_time, philo->index + 1);
		}
		pthread_mutex_unlock(&(philo->glob_info->print));
		pthread_mutex_lock(&(philo->glob_info->print));
		pthread_mutex_lock(&(philo->glob_info->eat_mutex));
		philo->last_eat = get_time();
		// usleep(10);
		pthread_mutex_unlock(&(philo->glob_info->eat_mutex)); ///////////
		if (!philo->glob_info->should_die)
		{	
			printf("%ld %d is eating\n", get_time() - philo->glob_info->start_time, philo->index + 1);
		}
		pthread_mutex_unlock(&(philo->glob_info->print));   
		// usleep(philo->glob_info->time_to_eat * 1000);
		while(get_time() - philo->last_eat < philo->glob_info->time_to_eat)
			usleep(200);
		// pthread_mutex_lock(&(philo->glob_info->eat_mutex)); ////////////
		// philo->glob_info->should_die[philo->index] += philo->glob_info->time_to_eat;
		// pthread_mutex_unlock(&(philo->glob_info->eat_mutex)); /////////
		// pthread_mutex_lock(&(philo->glob_info->eat_mutex));
		// if (check_eat_times(philo))
		// {
		// 	pthread_mutex_lock(&(philo->glob_info->print));
		// 	printf("%ld %d is sleeping\n", get_time() - philo->glob_info->start_time, philo->index + 1);
		// 	pthread_mutex_unlock(&(philo->glob_info->print)); 
		// 	usleep(philo->glob_info->time_to_sleep * 1000);
		// 	return NULL;
		// }
		// usleep(1000);
		// pthread_mutex_unlock(&(philo->glob_info->eat_mutex));
		pthread_mutex_unlock(&(philo->glob_info->forks[philo->lfid]));
		pthread_mutex_unlock(&(philo->glob_info->forks[philo->rfid]));
		pthread_mutex_lock(&(philo->glob_info->print));
		if (!philo->glob_info->should_die)
		{	
			philo->start_of_sleep = get_time();
			printf("%ld %d is sleeping\n", get_time() - philo->glob_info->start_time, philo->index + 1);
		}
		pthread_mutex_unlock(&(philo->glob_info->print));
		// usleep(philo->glob_info->time_to_sleep * 1000);
		while (get_time() - philo->start_of_sleep < philo->glob_info->time_to_sleep)
			usleep(200);
		// pthread_mutex_unlock(&(philo->glob_info->eat_mutex));////////
		// philo->glob_info->should_die[philo->index] += philo->glob_info->time_to_sleep;
		// pthread_mutex_unlock(&(philo->glob_info->eat_mutex));/////////////
		// printf("%ld %d is thinking\n", get_time() - philo->glob_info->start_time, (philo->index + 1));
	}
	return NULL;
}

void	*check_for_death(t_philo *philo)
{
	int i;

	i = 0;
	while(1)
	{
		i = 0;
		while (i < philo->glob_info->num_of_philo)
		{
			pthread_mutex_lock(&philo->glob_info->eat_mutex);
			if ((get_time() - philo[i].last_eat) >= philo->glob_info->time_to_die)
			{
				pthread_mutex_lock(&philo->glob_info->print);
				philo->glob_info->should_die = 1;
				printf("%ld %d died [%ld]\n", (get_time() - philo->glob_info->start_time), i + 1, (get_time() - philo[i].last_eat));
				pthread_mutex_unlock(&philo->glob_info->print);
				return NULL;
			}
			pthread_mutex_unlock(&philo->glob_info->eat_mutex);
			i++;	
		}
	}
}

int	threads_creation(t_philo *philo)
{
	int i;
	
	i = 0;
	philo->glob_info->start_time = get_time();
	while (i < philo->glob_info->num_of_philo)
	{
		philo[i].last_eat = get_time();
		pthread_create((&(philo[i].threads)), NULL, routine, &(philo[i]));
		usleep(10);
		// philo->glob_info->should_die[i] = 0;
		i++;
	}
	check_for_death(philo);
	// i = 0;
	// while (i < philo->glob_info->num_of_philo)
	// {
	// 	pthread_join((philo[i].threads), NULL);
	// 	i++;
	// }
	// i = 0;
	return (1);
}

int main(int ac, char *av[])
{
	t_glob_info *glob_info;
	t_philo *philo;
	int i;
	
	glob_info = malloc (sizeof(t_glob_info));
	if (ac < 5)
		return (0);
	glob_info->num_of_philo = ft_atoi(av[1]);
	glob_info->forks = malloc (sizeof(pthread_mutex_t) * glob_info->num_of_philo);
	glob_info->eat_times = malloc (sizeof(int *) * glob_info->num_of_philo);
	// glob_info->should_die = malloc (sizeof(int *) * glob_info->num_of_philo);
	glob_info->start_of_thinking = malloc(sizeof(int *) * glob_info->num_of_philo);
	i = 0;
	while (i < glob_info->num_of_philo)
	{
		pthread_mutex_init(&(glob_info->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(glob_info->eat_mutex), NULL);
	pthread_mutex_init(&(glob_info->print), NULL);
	philo = malloc (sizeof(t_philo) * glob_info->num_of_philo);
	glob_info->time_to_die = ft_atoi(av[2]);
	glob_info->time_to_eat = ft_atoi(av[3]);
	glob_info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		glob_info->max_eat_times = ft_atoi(av[5]);
	else
		glob_info->max_eat_times = 0;
	if (glob_info->num_of_philo == 0)
		return(0);
	i = 0;
	glob_info->should_die = 0;
	while (i < glob_info->num_of_philo)
	{
		philo[i].index = i;
		philo[i].lfid = (i + (glob_info->num_of_philo - 1)) % glob_info->num_of_philo;
		philo[i].rfid = i;
		philo[i].glob_info = glob_info;
		glob_info->eat_times[i] = 0;
		// philo[i].life = 0;
		i++;
	}
	
	if (!(threads_creation(philo)))
		return (0);
}