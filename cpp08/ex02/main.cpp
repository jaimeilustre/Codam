/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/12 15:31:20 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/13 21:18:38 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>

int main(void)
{
    std::cout << "=== STACK INITIALIZATION ===" << std::endl;

    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << "top(): " << mstack.top() << std::endl;

    mstack.pop();

    std::cout << "size(): " << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "=== FORWARD ITERATOR TEST ===" << std::endl;

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;

    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::cout << "=== CONST FORWARD ITERATOR TEST ===" << std::endl;

    const MutantStack<int> constStack(mstack);

    MutantStack<int>::constIterator cit = constStack.begin();
    MutantStack<int>::constIterator cite = constStack.end();

    while (cit != cite)
    {
        std::cout << *cit << std::endl;
        ++cit;
    }

    std::cout << "=== REVERSE ITERATOR TEST ===" << std::endl;

    MutantStack<int>::reverseIterator rit = mstack.rbegin();
    MutantStack<int>::reverseIterator rite = mstack.rend();

    while (rit != rite)
    {
        std::cout << *rit << std::endl;
        ++rit;
    }

    std::cout << "=== CONST REVERSE ITERATOR TEST ===" << std::endl;

    MutantStack<int>::constReverseIterator crit = constStack.rbegin();
    MutantStack<int>::constReverseIterator crite = constStack.rend();

    while (crit != crite)
    {
        std::cout << *crit << std::endl;
        ++crit;
    }

    std::cout << "=== COPY INTO STACK TEST ===" << std::endl;

    std::stack<int> s(mstack);
	
    std::cout << "Copied std::stack size(): " << s.size() << std::endl;

    return 0;
}
