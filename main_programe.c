/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_programe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issam <issam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:21:31 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 09:46:51 by issam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	while (1)
	{
		if (the_time() == 0 && philo->id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", the_time(), philo->id);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has teken a fork\n", the_time(), philo->id);
		philo->last_meal = the_time();
		printf("%lld %d is eating\n", the_time(), philo->id);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		if (philo->number_of_meals)
			philo->meals_count++;
		if (philo->number_of_meals && philo->number_of_meals <= philo->meals_count)
			break ;
		printf("%lld %d is sleeping\n", the_time(), philo->id);
		ft_usleep(philo->time_to_sleep);
		printf("%lld %d is thinking\n", the_time(), philo->id);
	}
	return (NULL);
}

int	check_eat(t_list *philo, int philo_size)
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

void	check_kill(t_list *philo, int philo_size, t_list *philo_head)
{
	while (1)
	{
		if ((the_time() - philo->last_meal) >= philo->time_to_die)
		{
			printf("%lld %d died\n", the_time(), philo->id);
			break ;
		}
		if ((philo->number_of_meals > 0) && check_eat(philo_head, philo_size))
		{
			break ;
		}
		usleep(100);
		philo = philo->next;
	}
}

int	main(int ac, char **av)
{
	t_list	*philo;
	t_list 	*philo_head;
	int		philo_size;
	int 	i = -1;

	if (check_args(ac, av))
		ft_error ();
	philo = create_philos(ac, av);
	philo_size = ft_atoi(av[1]);
	ft_lstlast(philo)->next = philo;
	philo_head = philo;
	while (--i < philo_size)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo->last_meal = 0;
		pthread_create(&philo->thread, NULL, &routine, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	check_kill(philo, philo_size, philo_head);

}