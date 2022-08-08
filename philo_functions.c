/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:42:52 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 17:40:19 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_error(void)
{
	write(2, "ERROR\n", 6);
	return (0);
}

int	spaces(const char *str)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)str;
	while ((s[i] >= 9 && s[i] <= 13) || (s[i] == 32))
	{
		i++;
	}
	return (i);
}

unsigned long long int	ft_atoi(char *s)
{
	int							i;
	int							sign;
	unsigned long long int		num;

	i = spaces(s);
	sign = 1;
	num = 0;
	if (s[i] == '+')
		i++;
	while (s[i] >= 48 && s[i] <= 57)
	{
		num = num * 10 + (s[i] - 48);
		i++;
	}
	return (num * sign);
}

t_philo	*ft_philo_new(int ac, char **av, \
		pthread_mutex_t *mutex_print, int *check)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->meals = 0;
	philo->number_of_meals = 0;
	philo->print = mutex_print;
	philo->check = check;
	philo->next = NULL;
	if (ac == 6)
		philo->number_of_meals = ft_atoi(av[5]);
	return (philo);
}

t_philo	*ft_philo_last(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while (philo->next)
			philo = philo->next;
	return (philo);
}
