/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:00:32 by ielmakhf          #+#    #+#             */
/*   Updated: 2022/08/07 16:56:31 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(int call, char *mssg, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld\t%d\t%s\n", get_time(), philo->id, mssg);
	if (call)
		pthread_mutex_unlock(philo->print);
}

int	check_meals(t_philo *philo)
{
	if (philo->number_of_meals && philo->meals >= philo->number_of_meals)
		return (1);
	return (0);
}

t_philo	*ft_creat(int ac, char **av, pthread_mutex_t *mutex_print, int *check)
{
	int	number_of_philos;
	int	i;
	t_philo	*head;
	t_philo *tmp;

	i = -1;
	number_of_philos = ft_atoi(av[1]);
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
		head->id = i + 2;
	}
	return (tmp);
}
