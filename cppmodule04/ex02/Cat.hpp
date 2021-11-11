#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	public:
		Cat();
		~Cat();
		Cat(Cat const &other);
		Cat &operator=(Cat const &other);
		void virtual makeSound() const;
		Brain & getBrain() const;
	private:
		Brain *brain;
};

#endif