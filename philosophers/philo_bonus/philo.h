/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:55:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 16:23:01 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

struct	s_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	sem_t			*death_sem;
	sem_t			*all_meals_sem;
	struct s_philo	*philos;
	int				deaths;
	size_t			start_time;
	bool			forks_sem_init;
	bool			print_sem_init;
	bool			meal_sem_init;
	bool			death_sem_init;
	bool			all_meals_sem_init;
}	t_data;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				meals_eaten;
	size_t			time_since_last_meal;
	t_data			*data;
	pthread_t		monitor_thread;
}	t_philo;

bool	valid_int(const char *str);
long	ft_strtol(const char *nptr);
size_t	get_current_time(void);
int		ft_usleep(size_t ms);
void	print_message(t_philo *philo, char *msg);

void	parse_and_init(int argc, char **argv, t_data *data);

void	free_and_close(t_data *data);
void	free_philos(t_data *data);
void	*routine(void *arg);
int		philo(int argc, char **argv);
int		main(int argc, char **argv);

void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	return_forks(t_philo *philo);
void	sleeping(t_philo *philo);

void	ft_putendl_fd(char *s, int fd);
void	exit_error(t_data *data, char *msg);

bool	create_philo_processes(t_data *data);
void	wait_and_handle_exit(t_data *data);
