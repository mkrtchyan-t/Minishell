#include "Animal.hpp"

Animal::Animal()
{
	this->type = "Animal";
	std::cout << "Animal Constructor" << std::endl;
}

Animal::~Animal()
{
	std::cout << "Animal Destructor" << std::endl;
}

void Animal::makeSound() const
{
	std::cout << "  " << std::endl;
}

std::string Animal::getType() const
{
	return (this->type);
}

Animal::Animal(Animal const &other)
{
	*this = other;
	std::cout << "Copy constructor Animal" << std::endl;
}

Animal &Animal::operator=(Animal const &other)
{
	this->type = other.type;
	return (*this);
	std::cout << "Animal assignment operator" << std::endl;
}
