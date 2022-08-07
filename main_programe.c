/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_programe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:21:31 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 17:42:11 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*(philo->check) == 0)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&philo->fork);
		print_status(1, "has teken a fork", philo);
		pthread_mutex_lock(&philo->next->fork);
		print_status(1, "has teken a fork", philo);
		philo->last_meal = the_time();
		print_status(1, "is eating", philo);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		if (philo->number_of_meals)
			philo->meals_count++;
		if (philo->number_of_meals && philo->number_of_meals <= philo->meals_count)
			break ;
		print_status(1, "is sleeping", philo);
		ft_usleep(philo->time_to_sleep);
		print_status(1, "is thinking", philo);
	}
	return (NULL);
}

int	check_eat(t_philo *philo, int philo_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo_size)
	{
		if (philo->meals_count >= philo->number_of_meals)
			j++;
		philo = philo->next;
		i++;
	}
	if (j == philo_size)
		return (1);
	return (0);
}

void	check_kill(t_philo *philo, int philo_size, t_philo *philo_head)
{
	while (1)
	{
		if ((the_time() - philo->last_meal) >= philo->time_to_die)
		{
			print_status(0, "is died", philo);
			*(philo->check) = 1;
			break ;
		}
		if ((philo->number_of_meals > 0) && check_eat(philo_head, philo_size))
		{
			break ;
		}
		philo = philo->next;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_philo 	*philo_head;
	int		philo_size;
	int 	i = -1;
	
	if (check_args(ac, av))
	{
		ft_error ();
		return (0);
	}
	philo = create_philos(ac, av);
	philo_size = ft_atoi(av[1]);
	ft_lstlast(philo)->next = philo;
	philo_head = philo;
	while (++i < philo_size)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo->last_meal = 0;
		pthread_create(&philo->thread, NULL, &routine, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	check_kill(philo, philo_size, philo_head);
	free(philo_head->print);
	free(philo->check);
	lstfree(philo_head, philo_size);
	return (0);
}