#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	this->type = "cat";
	std::cout << "Constructor cat" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "Cat destructor" << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << "cat's sound" << std::endl;
}