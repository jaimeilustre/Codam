/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:55:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 16:30:50 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

struct	s_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philos;
	int				deaths;
	size_t			start_time;
	bool			*forks_init;
	bool			print_mutex_init;
	bool			meal_mutex_init;
	bool			death_mutex_init;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			time_since_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

bool	valid_int(const char *str);
long	ft_strtol(const char *nptr);
size_t	get_current_time(void);
int		ft_usleep(size_t ms);
void	print_message(t_philo *philo, char *msg);

bool	parse_and_init(int argc, char **argv, t_data *data);

void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	return_forks(t_philo *philo);
void	sleeping(t_philo *philo);

bool	create_philo_thread(t_data *data);
void	*monitor(void *arg);

void	ft_putendl_fd(char *s, int fd);
int		exit_error(t_data *data, char *msg);

void	free_and_destroy(t_data *data);
void	*routine(void *arg);
int		philo(int argc, char **argv);
int		main(int argc, char **argv);
