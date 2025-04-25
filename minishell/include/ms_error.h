/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 18:02:48 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 18:19:44 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "ms_string.h"

typedef enum e_ms_error_code
{
	UNKNOWN = 0,	/* UNKNOWN should always be at the top assigned as zero */
	NO_PERM,
	NO_CMD,
	INVALID_ID,
	NO_ENV_VAR,
	TOO_N_ARGS,
	NUM_ARG_REQ,
	IS_DIR,
	AMB_REDIR,
	PERROR,			/* PERROR should always be at the bottom! */
}	t_ms_errno;

void	ms_error(int ms_errno, t_str str, t_str arg);

#endif
