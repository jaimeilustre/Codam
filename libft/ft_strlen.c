/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:33 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:08:00 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while(s[len])
        len++;
    return (len);
}

// #include <stdio.h>

// int main(void)
// {
//     char    *str = "Hello, world!";

//     printf("Length: %d\n", ft_strlen(str));
//     return (0);
// }