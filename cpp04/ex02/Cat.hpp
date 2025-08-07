/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:26:46 by jilustre      #+#    #+#                 */
/*   Updated: 2025/08/01 07:05:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat: public Animal
{
	public:
		Cat();
		Cat(const Cat& other);
		Cat&	operator=(const Cat& other);
		virtual ~Cat();

		void		makeSound() const override;
		void		setIdea(const std::string& idea, int index);
		std::string	getIdea(int index) const;
	private:
		Brain*	brain;
};

#endif