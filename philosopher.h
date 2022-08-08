/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 08:22:12 by issam             #+#    #+#             */
/*   Updated: 2022/08/07 17:39:47 by ielmakhf         ###   ########.fr       */
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
	pthread_t				thread;
	pthread_mutex_t			fork;
	pthread_mutex_t			*print;
	int						id;
	int						*check;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	last_meal;
	unsigned long long int	number_of_meals;
	unsigned long long int	meals;
	struct s_list			*next;
}				t_philo;

void					*simulation(void *arg);
unsigned long long int	ft_atoi(char *str);
int						check_args(int ac, char **av);
int						spaces(const char *str);
int						ft_error(void);
t_philo					*create_philos(int ac, char **av);
t_philo					*ft_philo_new(int ac, char **av, \
						pthread_mutex_t *mutex_print, int *check);
t_philo					*ft_philo_last(t_philo *philo);
unsigned long long int	get_time(void);
void					ft_usleep(unsigned long long int time);
int						check_eat(t_philo *philo, int philo_size);
void					philo_free(t_philo *philo, int philo_size, \
						t_philo *philo_head);
void					print_status(int call, char *mssg, t_philo *philo);
int						check_meals(t_philo *philo);
t_philo					*ft_creat(int ac, char **av, pthread_mutex_t *mutex_print, int *check);

#endif