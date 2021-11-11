#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	this->type = "Animal";
	std::cout << "Animal Constructor" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "Animal Destructor" << std::endl;
}

void WrongAnimal::makeSound() const
{
	std::cout << "hiiii  " << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (this->type);
}