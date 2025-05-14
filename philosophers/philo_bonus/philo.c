/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/14 16:31:41 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*Frees the forks array and destroys the mutexes*/
void	free_and_close(t_data *data)
{
	if (data->forks_sem_init)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->philos)
		free(data->philos);
	if (data->meal_sem_init)
	{
		sem_close(data->meal_sem);
		sem_unlink("/meal");
	}
	if (data->print_sem_init)
	{
		sem_close(data->print_sem);
		sem_unlink("/print");
	}
	if (data->death_sem_init)
	{
		sem_close(data->death_sem);
		sem_unlink("/death");
	}
}

/*Checks if any deaths occured during the simulation*/
static bool	death_check(t_data *data)
{
	bool	status;

	sem_wait(data->death_sem);
	status = data->deaths;
	sem_post(data->death_sem);
	return (status);
}

/*Philosopher's routine*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(10);
	while (1)
	{
		if (death_check(philo->data))
			break ;
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		if (death_check(philo->data))
			break ;
		sleeping(philo);
		if (philo->data->max_meals > 0
			&& philo->meals_eaten >= philo->data->max_meals)
			break ;
	}
	return (NULL);
}

/*Main program logic*/
int	philo(int argc, char **argv)
{
	t_data		data;
	pid_t		monitor_pid;
	int			i;
	int			status;

	if (!parse_args(argc, argv, &data))
		exit_error(&data, "Error with parsing");
	if (!init_data(&data))
		exit_error(&data, "Error with initialising");
	if (!init_semaphores(&data))
		exit_error(&data, "Error with mutex");
	init_philos(&data);
	data.start_time = get_current_time();
	if (!create_philo_processes(&data))
		exit_error(&data, "Error with creating philo processes");
	monitor_pid = fork();
	if (monitor_pid < 0)
		exit_error(&data, "Error with forking");
	if (monitor_pid == 0)
	{
		monitor(&data);
		exit(EXIT_SUCCESS);
	}
	// waitpid(monitor_pid, &status, 0);
	// i = 0;
	// while (i < data.nb_of_philos)
	// {
	// 	kill(data.philos[i].pid, SIGKILL);
	// 	i++;
	// }
	// i = 0;
	// while (i < data.nb_of_philos)
	// {
	// 	waitpid(data.philos[i].pid, NULL, 0);
	// 	i++;
	// }
	// Wait for any child to exit (i.e. philosopher death or success)
	monitor_pid = waitpid(-1, &status, 0);
	// One philosopher died or finished; terminate all others
	i = 0;
	while (i < data.nb_of_philos)
	{
		if (data.philos[i].pid != monitor_pid) // Don't kill the one that exited
			kill(data.philos[i].pid, SIGTERM);
		i++;
	}
	free_and_close(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6)
		philo(argc, argv);
	else if (argc <= 4)
		ft_putendl_fd("Too few arguments", 2);
	else
		ft_putendl_fd("Too many arguments", 2);
	return (0);
}
