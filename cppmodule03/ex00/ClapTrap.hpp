#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
	private:
		std::string name;
		int hitPoints;
		int energyPoints;
		int attackDamage;
	public:
		ClapTrap(std::string name);
		~ClapTrap();
		std::string getName() const;
		int getHitPoints() const;
		int getEnergyPoints() const;
		int getAttackDamage() const;
		void setHitPoints(unsigned int points);
		void setEnergyPoints(unsigned int points);
		void setAttackDamage(unsigned int damage);
		void attack(std::string const &attack);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

# endif
