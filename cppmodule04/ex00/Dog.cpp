#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog constructor" << std::endl;
	this->type = "Dog";
}

Dog::~Dog()
{
	std::cout << "Dog destructor" << std::endl;
}


void Dog::makeSound() const
{
	std::cout << "dog's sound" << std::endl;
}