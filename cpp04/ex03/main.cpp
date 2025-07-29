/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 10:00:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/29 08:04:30 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

// int main(void)
// {
// 	std::cout << "\n--- SETUP ---\n";
// 	IMateriaSource* src = new MateriaSource();
// 	src->learnMateria(new Ice());
// 	src->learnMateria(new Cure());

// 	ICharacter* me = new Character("me");

// 	AMateria* tmp;

// 	std::cout << "\n--- EQUIP TEST (2 Materias) ---\n";
// 	tmp = src->createMateria("ice");
// 	me->equip(tmp);
// 	tmp = src->createMateria("cure");
// 	me->equip(tmp);

// 	std::cout << "\n--- USE TEST (valid use) ---\n";
// 	ICharacter* bob = new Character("bob");
// 	me->use(0, *bob); // shoot ice bolt
// 	me->use(1, *bob); // heal wounds

// 	std::cout << "\n--- EQUIP TEST (more than 4 slots) ---\n";
// 	me->equip(src->createMateria("ice"));
// 	me->equip(src->createMateria("cure"));
// 	me->equip(src->createMateria("ice")); // 5th: should be ignored

// 	std::cout << "\n--- USE TEST (invalid indexes) ---\n";
// 	me->use(-1, *bob); // nothing should happen
// 	me->use(4, *bob);  // nothing should happen

// 	std::cout << "\n--- UNEQUIP TEST ---\n";
// 	me->unequip(1); // unequip Cure
// 	me->use(1, *bob); // nothing should happen

// 	std::cout << "\n--- CREATE UNKNOWN MATERIA ---\n";
// 	AMateria* unknown = src->createMateria("fire");
// 	if (!unknown)
// 		std::cout << "Unknown materia type 'fire'\n";

// 	std::cout << "\n--- DEEP COPY TEST ---\n";
// 	Character* original = new Character("original");
// 	original->equip(src->createMateria("ice"));
// 	original->equip(src->createMateria("cure"));

// 	Character copy = *original; // copy constructor
// 	std::cout << "[Original uses index 0] ";
// 	original->use(0, *bob);
// 	std::cout << "[Copy uses index 0] ";
// 	copy.use(0, *bob);

// 	delete original;

// 	std::cout << "\n--- CLEANUP ---\n";
// 	delete bob;
// 	delete me;
// 	delete src;

// 	return (0);
// }

int main(void)
{
	std::cout << "\n--- SETUP ---\n";
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	Character* me = new Character("me");

	std::cout << "\n--- EQUIP TEST (2 Materias) ---\n";
	if (me->hasInventorySpace())
		me->equip(src->createMateria("ice"));
	if (me->hasInventorySpace())
		me->equip(src->createMateria("cure"));

	std::cout << "\n--- USE TEST (valid use) ---\n";
	Character* bob = new Character("bob");
	me->use(0, *bob); // shoot ice bolt
	me->use(1, *bob); // heal wounds

	std::cout << "\n--- EQUIP TEST (more than 4 slots) ---\n";
	if (me->hasInventorySpace())
		me->equip(src->createMateria("ice"));
	if (me->hasInventorySpace())
		me->equip(src->createMateria("cure"));
	if (me->hasInventorySpace())
		me->equip(src->createMateria("ice")); // 5th: should be skipped

	std::cout << "\n--- USE TEST (invalid indexes) ---\n";
	me->use(-1, *bob); // nothing should happen
	me->use(4, *bob);  // nothing should happen

	std::cout << "\n--- UNEQUIP TEST ---\n";
	me->unequip(1); // unequip Cure
	me->use(1, *bob); // nothing should happen

	std::cout << "\n--- CREATE UNKNOWN MATERIA ---\n";
	AMateria* unknown = src->createMateria("fire");
	if (!unknown)
		std::cout << "Unknown materia type 'fire'\n";

	std::cout << "\n--- DEEP COPY TEST ---\n";
	Character* original = new Character("original");
	if (original->hasInventorySpace())
		original->equip(src->createMateria("ice"));
	if (original->hasInventorySpace())
		original->equip(src->createMateria("cure"));

	Character copy = *original; // invokes copy constructor
	std::cout << "[Original uses index 0] ";
	original->use(0, *bob);
	std::cout << "[Copy uses index 0] ";
	copy.use(0, *bob);
	
	delete original;

	std::cout << "\n--- CLEANUP ---\n";
	delete bob;
	delete me;
	delete src;

	return 0;
}

