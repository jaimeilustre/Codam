/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 11:29:22 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/13 15:38:42 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "ms_string.h"

void	swap_ptr(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swapi(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_cstr	join_pair(t_cstr left, t_cstr right, char *sep)
{
	size_t	len;
	size_t	curr_len;
	t_str	entry;

	len = ft_strlen(left) + ft_strlen(right) + ft_strlen(sep) + 1;
	entry = ft_calloc(len, sizeof(char));
	if (entry == NULL)
		return (NULL);
	curr_len = ft_strlcat(entry, left, len);
	curr_len = ft_strlcat(entry + curr_len, sep, len);
	ft_strlcat(entry + curr_len, right, len);
	return (entry);
}
