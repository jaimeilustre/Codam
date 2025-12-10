/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 22:12:46 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/10 09:53:59 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Array.hpp"

int main(void)
{
    std::cout << "=== DEFAULT CONSTRUCTOR ===" << std::endl;
	
    Array<int> test1;
	
    std::cout << "test1.size() = " << test1.size() << std::endl;

    std::cout << "=== SIZED CONSTRUCTOR ===" << std::endl;
	
    Array<int> test2(5);
	
    for (unsigned int i = 0; i < test2.size(); ++i)
        test2[i] = i + 1;
 
    for (unsigned int i = 0; i < test2.size(); ++i)
        std::cout << test2[i] << " ";
    std::cout << std::endl;

	std::cout << "=== COPY CONSTRUCTOR ===" << std::endl;
	
    Array<int> test3(test2);
	
    test3[0] = 42;
    std::cout << "test2[0] = " << test2[0] << " Expected: 1" << std::endl;
    std::cout << "test3[0] = " << test3[0] << " Expected: 42" << std::endl;

    std::cout << "=== COPY ASSIGNMENT OPERATOR ===" << std::endl;
	
    Array<std::string> test4(3);
	
    test4[0] = "hello";
    test4[1] = "42";
    test4[2] = "world";

    Array<std::string> test5;
	
    test5 = test4;
    test5[0] = "changed";

    std::cout << "test4[0] = " << test4[0] << std::endl; // should remain "hello"
    std::cout << "test5[0] = " << test5[0] << std::endl; // should be "changed"

    std::cout << "=== OUT OF BOUNDS TEST ===" << std::endl;
	
    try
	{
        std::cout << test5[3] << std::endl;
    }
	catch (std::exception &e)
	{
        std::cout << "Out of bounds exception" << std::endl;
    }

	std::cout << "=== EMPTY ARRAY TEST ===" << std::endl;
	
    try
	{
        Array<int> empty;
        empty[0] = 1;
    }
	catch (std::exception &e)
	{
        std::cout << "Empty array exception" << std::endl;
    }

    return (0);
}
