/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:26:46 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/31 05:03:43 by jaimeilustr   ########   odam.nl         */
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
		~Cat() override;

		void		makeSound() const override;
		Animal*		clone() const override;
		void		setIdea(const std::string& idea, int index);
		std::string	getIdea(int index) const;
	private:
		Brain*	brain;
};

#endif