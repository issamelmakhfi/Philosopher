/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issam <issam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:42:52 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 09:34:42 by issam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_error(void)
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
	int		                    i;
	int		                    sign;
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

t_list	*ft_lstnew(int argc, char **argv)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	if (philo == NULL)
		return (NULL);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->meals_count = 0;
	philo->number_of_meals = 0;
	philo->next = NULL;
	if (argc == 6)
		philo->number_of_meals = ft_atoi(argv[5]);
	return (philo);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
			lst = lst->next;
	return (lst);
}