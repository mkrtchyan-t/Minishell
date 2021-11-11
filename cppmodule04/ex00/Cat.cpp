#include "Cat.hpp"

Cat::Cat()
{
	this->type = "cat";
	std::cout << "Constructor cat" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat destructor" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "cat's sound" << std::endl;
}