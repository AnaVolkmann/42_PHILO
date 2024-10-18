/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:56:10 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/18 14:53:14 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** @brief Checks if the value of dead_flag changed */
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
/** @ brief thread routine */
void *philo_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
	{
		ft_usleep(1);
	}
	while(!dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (pointer);
}

/** @brief creates all the threads */
int	create_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	god;
	int			i;

	if (pthread_create(&god, NULL, &monitor, program->philos) != 0)
		destroy_all("Thread creation failed", program, forks);
	i = 0;
	while(i < program->philos[0].num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join failed", program, forks);
		i++;
	}
	return (0);
}