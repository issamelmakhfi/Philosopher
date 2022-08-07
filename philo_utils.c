/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issam <issam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:31:47 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 09:38:01 by issam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long long int	the_time(void)
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

int check_args(int ac, char **av)
{
    int i;

    i = 0;
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

t_list	*create_philos(int ac, char **av)
{
	int		number_of_philos;
	int		i;
	t_list	*head;
	t_list	*tmp;

	number_of_philos = ft_atoi(av[1]);
	i = 0;
	while (i < number_of_philos)
	{
		if (i == 0)
		{
			head = ft_lstnew(ac, av);
			tmp = head;
		}
		else
		{
			head->next = ft_lstnew(ac, av);
			head = head->next;
		}
		head->id = i + 1;
		i++;
	}
	return (tmp);
}

void	ft_usleep(unsigned long long int time)
{
	unsigned long long int start;

	start = the_time();
	while ((the_time() - start) < time)
	{
		usleep(100);
	}
}