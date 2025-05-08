/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/08 17:10:55 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data data;
	
	if (!parse_args(argc, argv, &data))
		printf("Error");	
	if (!init_mutex(&data))
		printf("Error");
	if (!init_data(&data))
		printf("Error");
	init_philos(&data);
	return (0);
}
