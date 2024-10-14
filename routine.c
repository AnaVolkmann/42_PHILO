/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:10:20 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:21 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//eat
//sleep
//think

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	sleep(t_philo *philo)
{
	print_messgae("is sleeping", philo, philo->id);
	ft_usleep(philo->t_sleep);
}