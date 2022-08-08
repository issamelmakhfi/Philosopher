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
	static unsigned long long int	start;

	gettimeofday(&time, NULL);
	time_spent = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start == 0)
		start = time_spent;
	return (time_spent - start);
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
	int				number_of_philos;
	int				i;
	t_philo			*head;
	t_philo			*tmp;
	pthread_mutex_t	*mutex_print;
	int				*check;

	check = (int *)malloc(sizeof(int));
	mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	*check = 0;
	pthread_mutex_init(mutex_print, NULL);
	number_of_philos = ft_atoi(av[1]);
	// tmp = ft_creat(head, mutex_print, check);
	i = -1;
	while (++i < number_of_philos)
	{
		if (i == 0)
		{
			head = ft_philo_new(ac, av, mutex_print, check);
			tmp = head;
		}
		else
		{
			head->next = ft_philo_new(ac, av, mutex_print, check);
			head = head->next;
		}
		head->id = i + 1;
	}
	return (tmp);
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
	free(philo->check);
	while (++i < philo_size)
	{
		philo_next = tmp->next;
		free(tmp);
		tmp = philo_next;
	}
}
