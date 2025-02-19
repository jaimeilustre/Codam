/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deadlock.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 15:06:22 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/19 17:09:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*Deadlock: occurs when two or more threads are stuck waiting for each other to release resources
and none can proceed*/

pthread_mutex_t	lock1;
pthread_mutex_t	lock2;

void	*thread1()
{
	pthread_mutex_lock(&lock1);
	printf("Thread 1: Locked lock1\n");
	sleep(1);

	printf("Thread 1: Waiting for lock2... \n");
	pthread_mutex_lock(&lock2); // DEADLOCK: Thread 2 already locked lock2
	printf("Thread 1: Acquired lock2\n");
	
	pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);

	return (NULL);
}

void	*thread2()
{
	pthread_mutex_lock(&lock2);
	printf("Thread 2: Locked lock2\n");
	sleep(1);

	printf("Thread 2: Waiting for lock1... \n");
	pthread_mutex_lock(&lock1); // DEADLOCK: Thread 1 already locked lock1
	printf("Thread 2: Acquired lock1\n");
	
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);

	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&lock1, NULL);
	pthread_mutex_init(&lock2, NULL);
	
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);

	return (0);
}

// Both threads are waiting for each other indefinitely: DEADLOCK

/*Preventing deadlock: always lock mutexes in the same order*/

pthread_mutex_t	lock1;
pthread_mutex_t	lock2;

void	*thread1()
{
	pthread_mutex_lock(&lock1);
	sleep(1);
	pthread_mutex_lock(&lock2); // Lock in the same order as thread2
	printf("Thread 1: Acquired both locks\n");
	
	pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);

	return (NULL);
}

void	*thread2()
{
	pthread_mutex_lock(&lock1);
	sleep(1);
	pthread_mutex_lock(&lock2); // Lock in the same order as thread 1
	printf("Thread 2: Acquired both locks\n");
	
	pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);

	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&lock1, NULL);
	pthread_mutex_init(&lock2, NULL);
	
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);

	return (0);
}
