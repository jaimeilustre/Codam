/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   IMateriaSource.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/22 17:14:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/28 10:58:51 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() {};
		virtual void	learnMateria(AMateria*) = 0;
		virtual AMateria*	createMateria(std::string const& type) = 0;
};

#endif