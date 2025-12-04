/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Functions.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 10:14:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/04 10:16:31 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

# include <ctime>
# include <iostream>

# include "A.hpp"
# include "B.hpp"
# include "C.hpp"

Base*	generate(void);
void	identify(Base *p);
void	identify(Base& p);

#endif

