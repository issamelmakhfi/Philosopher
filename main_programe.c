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

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (*(philo->check) == 1)
	// 	printf("teeeeeeeeeeeeeeeest\n");
	if (philo->id % 2)
		usleep(100);
	while (*(philo->check) == 0)
	{
		pthread_mutex_lock(&philo->fork);
		print_status(1, "has teken a fork", philo);
		pthread_mutex_lock(&philo->next->fork);
		print_status(1, "has teken a fork", philo);
		philo->last_meal = get_time();
		print_status(1, "is eating", philo);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		if (philo->number_of_meals)
			philo->meals++;
		if (check_meals(philo))
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
		if (philo->meals >= philo->number_of_meals)
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
		if ((get_time() - philo->last_meal) >= philo->time_to_die)
		{
			*(philo->check) = 1;
			print_status(0, "is died", philo);
			break ;
		}
		if ((philo->number_of_meals > 0) && check_eat(philo_head, philo_size))
			break ;
		philo = philo->next;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_philo	*philo_head;
	int		philo_size;
	int		i;

	i = -1;
	if (check_args(ac, av))
	{
		ft_error ();
		return (0);
	}
	philo = create_philos(ac, av);
	philo_size = ft_atoi(av[1]);
	ft_philo_last(philo)->next = philo;
	philo_head = philo;
	while (++i < philo_size)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo->last_meal = 0;
		pthread_create(&philo->thread, NULL, &simulation, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	check_kill(philo, philo_size, philo_head);
	return (philo_free(philo_head, philo_size, philo_head), 0);
}
