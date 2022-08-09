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
#include <string.h>

void	print_status(int call, char *mssg, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld\t%d\t%s\n", get_time(), philo->id, mssg);
	if (call == 1)
		pthread_mutex_unlock(philo->print);
}

int	check_meals(t_philo *philo)
{
	if (philo->number_of_meals && philo->meals >= philo->number_of_meals)
		return (1);
	return (0);
}

t_philo	*ft_creat(int ac, char **av, pthread_mutex_t *mutex_print)
{
	int		number_of_philos;
	int		i;
	t_philo	*head;
	t_philo	*tmp;

	i = -1;
	number_of_philos = ft_atoi(av[1]);
	while (++i < number_of_philos)
	{
		if (i == 0)
		{
			head = init_data(ac, av, mutex_print);
			tmp = head;
		}
		else
		{
			head->next = init_data(ac, av, mutex_print);
			head = head->next;
		}
		head->id = i + 1;
	}
	return (tmp);
}
