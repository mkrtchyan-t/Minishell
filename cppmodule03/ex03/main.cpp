#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap diamond("coucou");
	diamond.attack("coucou");
	diamond.takeDamage(3);
	diamond.beRepaired(2);
	diamond.whoami();
	
}
