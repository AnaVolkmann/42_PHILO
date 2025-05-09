/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:36:17 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/29 15:34:29 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Makes the philosopher think and prints the corresponding message.
 *
 * This function calls the print_message function to indicate that the
 * philosopher is in the thinking state.
 *
 * @param philo Pointer to the philosopher structure.
 */
void	ft_think(t_philo *philo)
{
	size_t	t_think;

	t_think = (philo->time_to_eat - philo->time_to_sleep + 1);
	print_message("is thinking", philo, philo->id);
	if (philo->id % 2 != 0)
		ft_usleep(t_think);
}

/**
 * @brief Makes the philosopher sleep for a specified
 * duration and prints the corresponding message.
 *
 * This function calls the print_message function to indicate that the
 * philosopher is sleeping, then it invokes ft_usleep to pause
 * execution for the specified sleep duration.
 *
 * @param philo Pointer to the philosopher structure.*/
void	ft_sleep(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	take_forks(t_philo *philo, pthread_mutex_t **left,
			pthread_mutex_t **right)
{
	*left = philo->l_fork;
	*right = philo->r_fork;
	if (philo->id % 2 == 1)
	{
		*left = philo->r_fork;
		*right = philo->l_fork;
	}
	pthread_mutex_lock(*left);
	print_message("has taken a fork", philo, philo->id);
}

/**
 * @brief Controls the eating process for the philosopher.
 *
 * This function manages the locking of forks, updates meal statistics,
 * and ensures that if there is only one philosopher, they cannot eat
 * and will simply wait until they die.
 - If there's only one philosopher, they can't eat, so just wait to die.
 * @param philo Pointer to the philosopher structure.*/
void	ft_eat(t_philo *philo)
{
	pthread_mutex_t	*tmp_left;
	pthread_mutex_t	*tmp_right;

	take_forks(philo, &tmp_left, &tmp_right);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(tmp_left);
		return ;
	}
	pthread_mutex_lock(tmp_right);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(tmp_right);
	pthread_mutex_unlock(tmp_left);
}
