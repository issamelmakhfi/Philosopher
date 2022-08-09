/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:31:47 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 17:39:38 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long long int	get_time(void)
{
	struct timeval					time;
	unsigned long long int			time_spent;
	static unsigned long long int	ref;

	gettimeofday(&time, NULL);
	time_spent = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (ref == 0)
		ref = time_spent;
	return (time_spent - ref);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6)
		return (1);
	if (ac < 5)
		return (2);
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (3);
		i++;
	}
	return (0);
}

t_philo	*create_philos(int ac, char **av)
{
	t_philo			*head;
	pthread_mutex_t	*mutex_print;

	mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_print, NULL);
	head = ft_creat(ac, av, mutex_print);
	return (head);
}

void	ft_usleep(unsigned long long int time)
{
	unsigned long long int	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(100);
	}
}

void	philo_free(t_philo *philo, int philo_size, t_philo *philo_head)
{
	int		i;
	t_philo	*philo_next;
	t_philo	*tmp;

	tmp = philo;
	i = -1;
	free(philo_head->print);
	while (++i < philo_size)
	{
		philo_next = tmp->next;
		free(tmp);
		tmp = philo_next;
	}
}
