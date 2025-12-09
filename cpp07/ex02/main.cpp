/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 22:12:46 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/09 22:32:07 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Array.hpp"

int main(void)
{
    std::cout << "=== DEFAULT CONSTRUCTOR ===" << std::endl;
	
    Array<int> a;
	
    std::cout << "a.size() = " << a.size() << std::endl;

    std::cout << "=== SIZED CONSTRUCTOR ===" << std::endl;
	
    Array<int> b(5);
	
    for (unsigned int i = 0; i < b.size(); ++i)
        b[i] = i + 1;
 
    for (unsigned int i = 0; i < b.size(); ++i)
        std::cout << b[i] << " ";
    std::cout << std::endl;

	std::cout << "=== COPY CONSTRUCTOR ===" << std::endl;
	
    Array<int> c(b);
	
    c[0] = 42;
    std::cout << "b[0] = " << b[0] << " (should be 1)\n";
    std::cout << "c[0] = " << c[0] << " (should be 42)\n";

    std::cout << "=== COPY ASSIGNMENT OPERATOR ===" << std::endl;
	
    Array<std::string> s1(3);
	
    s1[0] = "hello";
    s1[1] = "42";
    s1[2] = "world";

    Array<std::string> s2;
	
    s2 = s1;
    s2[0] = "changed";

    std::cout << "s1[0] = " << s1[0] << std::endl; // should remain "hello"
    std::cout << "s2[0] = " << s2[0] << std::endl; // should be "changed"

    std::cout << "=== OUT OF BOUNDS TEST ===" << std::endl;
	
    try
	{
        std::cout << b[100] << std::endl;
    }
	catch (std::exception &e)
	{
        std::cout << "Caught exception for out-of-bounds (good)" << std::endl;
    }

	std::cout << "=== EMPTY ARRAY TEST ===" << std::endl;
	
    try
	{
        Array<int> empty;
        empty[0] = 1;
    }
	catch (std::exception &e)
	{
        std::cout << "Caught exception for empty array indexing (good)" << std::endl;
    }

    return (0);
}