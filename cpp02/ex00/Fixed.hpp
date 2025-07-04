/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:22:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 08:19:00 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
	public:
		Fixed();
		Fixed(const Fixed& other);
		Fixed&	operator=(const Fixed& other);
		~Fixed();
		
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
	private:
		int					_fixedPointNumber;
		static const int	_fractionalBits = 8;
};

#endif