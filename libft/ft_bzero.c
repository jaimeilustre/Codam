/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:46:46 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:17:21 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[3] = {"abc"};

// 	ft_bzero(str, 2);

// 	int i;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	return (0);
// }