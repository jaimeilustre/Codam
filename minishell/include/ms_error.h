/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 18:02:48 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/02 09:25:49 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "ms_string.h"

# define MS_ERROR_MAX 9

typedef enum e_ms_error_code
{
	UNKNOWN = 0,
	NO_PERM = 1,
	NO_CMD = 2,
	NO_FILE_DIR = 3,
	NO_ALLOC = 4,
	INVALID_ID = 5,
	NO_ARGS = 6,
	NO_ENV_VAR = 7,
	TOO_N_ARGS = 8,
	PERROR = 9,
}	t_ms_errno;

void	ms_error(int ms_errno, t_str str, t_str arg);

#endif
