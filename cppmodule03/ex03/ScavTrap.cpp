#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "Scav Trap constructor" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
}

ScavTrap::~ScavTrap()
{
	std::cout << "Scav Trap destructor" << std::endl;
}

void ScavTrap::attack(std::string const &target)
{
	std::cout << "Scav Trap " << this->name << " attack "\
        << target << " causing " << this->hitPoints
        << " points of damage"
        << std::endl;
}

void ScavTrap::guardgate()
{
	std::cout << "gate keeper  mode" << std::endl;
}
