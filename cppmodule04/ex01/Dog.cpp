#include "Dog.hpp"

Dog::Dog()
{
	this->brain = new Brain();
	std::cout << "Dog constructor" << std::endl;
	this->type = "Dog";
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog destructor" << std::endl;
}

Dog::Dog(Dog const &other)
{
	*this = other;
	std::cout << "Copy constructor dog" << std::endl;
}

Dog &Dog::operator=(Dog const &other)
{
	this->type = other.type;
	this->brain = new Brain(*other.brain);
	return (*this);
	std::cout << "Dog assignment operator" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "dog's sound" << std::endl;
}

Brain &Dog::getBrain() const
{
	return (*this->brain);
}