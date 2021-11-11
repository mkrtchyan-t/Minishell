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