#include "Cat.hpp"

Cat::Cat()
{
	this->brain = new Brain();
	this->type = "cat";
	std::cout << "Constructor cat" << std::endl;
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat destructor" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "cat's sound" << std::endl;
}

Cat::Cat(Cat const &other)
{
	*this = other;
	std::cout << "Copy constructor Cat" << std::endl;
}

Cat &Cat::operator=(Cat const &other)
{
	this->type = other.type;
	this->brain = new Brain(*other.brain);
	return (*this);
	std::cout << "Cat assignment operator" << std::endl;
}

Brain &Cat::getBrain() const
{
	return (*this->brain);
}