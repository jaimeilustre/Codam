/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:33 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/08 10:09:52 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while(str[len])
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