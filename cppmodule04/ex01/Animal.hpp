#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
	protected:
		std::string type;
	public:
		Animal();
		virtual ~Animal();
		Animal(Animal const &other);
		Animal &operator=(Animal const &other);
		void virtual makeSound() const;
		std::string getType() const;
};

#endif