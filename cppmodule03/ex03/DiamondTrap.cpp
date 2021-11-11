#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name)
{
	std::cout << "Diamond Trap Constuctor called" << std::endl;
	this->name = name;
	this->hitPoints = FragTrap::hitPoints;
	this->energyPoints = ScavTrap::energyPoints;
	this->attackDamage = FragTrap::attackDamage;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "Diamond Trap " << this->name << " destructor " << std::endl;
}

void DiamondTrap::attack(std::string const &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoami()
{
	std::cout << "DiamondTrap name " << this->name <<" ClapTrap name "<< ClapTrap::name << std::endl;
}