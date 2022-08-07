/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issam <issam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:22:12 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 09:38:10 by issam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_list
{
    pthread_t	thread;
	pthread_mutex_t		fork;
	int					id;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	last_meal;
	unsigned long long int	number_of_meals;
	unsigned long long int	meals_count;
	struct s_list			*next;
}				t_list;

unsigned long long int	ft_atoi(char *str);
int check_args(int ac, char **av);
int	spaces(const char *str);
int ft_error(void);
t_list	*create_philos(int ac, char **av);
t_list	*ft_lstnew(int argc, char **argv);
t_list	*ft_lstlast(t_list *lst);
unsigned long long int	the_time(void);
void	ft_usleep(unsigned long long int time);

#endif