/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:08 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:09:56 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c > 0 || c > 255)
		return (0);
	return (ft_isalpha(c) || ft_isdigit(c));
}
