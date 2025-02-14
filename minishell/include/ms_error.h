/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 18:02:48 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/13 11:14:49 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "ms_string.h"

# define MS_ERROR_MAX 5

typedef enum e_ms_error_code
{
	UNKNOWN = 0,
	NO_PERM = 1,
	NO_CMD = 2,
	NO_FILE_DIR = 3,
	NO_ALLOC = 4,
	PERROR = 5
}	t_ms_errno;

void	ms_error(int ms_errno, t_str str);

#endif
