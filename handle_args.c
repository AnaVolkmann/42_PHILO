/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:48:45 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/24 17:24:21 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks if the input string contains only numeric characters.
 *
 * This function verifies that all characters in the input string
 * are digits (0-9). 
 *
 * @param argv The input string to check.
 * @return 1 if the string contains non-numeric characters, 0 otherwise.
 */
int	check_args(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Validates the command-line arguments provided to the program.
 *
 * This function checks each argument for validity, ensuring that
 * they are positive integers within acceptable ranges. If any
 * argument is invalid, an appropriate error message is written to
 * standard error.
 *
 * @param argv Array of command-line arguments.
 * @return 1 if any argument is invalid, 0 otherwise.
 */
int	valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_args(argv[1]) == 1)
		return (write(2, "Invalid number of philosophers\n", 31), 1);
	if (ft_atoi(argv[2]) <= 0 || check_args(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_args(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_args(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_args(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
