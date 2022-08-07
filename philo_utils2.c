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

void    print_status(int call, char *mssg, t_philo *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%lld\t%d\t%s\n", the_time(), philo->id, mssg);
    if (call)
        pthread_mutex_unlock(philo->print);
}