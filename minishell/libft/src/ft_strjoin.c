/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:01:54 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:56 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_1;
	size_t	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	dst = malloc((len_1 + len_2 + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1, len_1);
	ft_memcpy(dst + len_1, s2, len_2);
	*(dst + len_1 + len_2) = '\0';
	return (dst);
}
