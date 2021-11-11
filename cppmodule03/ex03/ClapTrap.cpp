#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
{
	std::cout << "Clap Trap constructor called" << std::endl;
	this->name = name;
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Clap Trap destructor called" << std::endl;
}

void ClapTrap::attack(std::string const &target)
{
	std::cout << "Clap Trap " << this->name << " attack "\
	<< target << " causing " << this->hitPoints
	<< " points of damage"
	<< std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (amount >= this->hitPoints)
	{
		this->hitPoints = 0;
	}
	else
		this->hitPoints -= amount;
	this->attackDamage = amount;
	std::cout << "ClapTrap " << this ->name << " lost " << amount <<\
	" points" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->hitPoints + amount <= 10)
		this->hitPoints += amount;
	std::cout << "ClapTrap " << this->name << " repaired " \
	<< amount << std::endl;
}

std::string ClapTrap::getName() const
{
	return (this->name);      
}

int ClapTrap::getHitPoints() const
{
	return (this->hitPoints);
}

int ClapTrap::getEnergyPoints() const
{
	return (this->energyPoints);
}

int ClapTrap::getAttackDamage() const
{
	return (this->attackDamage);
}

void ClapTrap::setHitPoints(unsigned int points)
{
	this->hitPoints = points;
}

void ClapTrap::setEnergyPoints(unsigned int points)
{
	this->energyPoints = points;
}

void ClapTrap::setAttackDamage(unsigned int damage)
{
	this->attackDamage = damage;
}
