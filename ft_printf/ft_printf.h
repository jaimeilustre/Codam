/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:50:33 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/28 07:15:16 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft/libft.h"

int	print_char(int c);
int	print_str(char *str);
int	print_int(int nb);
int	print_hex(unsigned int nb, int uppercase);
int	print_hex_ptr(uintptr_t ptr);

#endif