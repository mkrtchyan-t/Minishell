#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public virtual ClapTrap
{
	public:
		ScavTrap(std::string name);
		~ScavTrap();
		void attack(std::string const &target);
		void guardgate();
};

#endif
