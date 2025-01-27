/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 09:50:33 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/23 09:36:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_int(int nb);
int	ft_print_hex(unsigned int nb, int uppercase);
int	ft_print_ptr(uintptr_t ptr);
int	ft_print_unsigned(unsigned int nb);
int	ft_printf(const char *str, ...);

#endif