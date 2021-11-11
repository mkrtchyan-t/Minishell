#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	Dog shpic;
	shpic.getBrain().addIdea("eat a cat");
	{
		Dog tmp = shpic;
	}
	std::cout << "getideas of shpic - " << shpic.getBrain().getIdeas() << std::endl;
	delete j;//should not create a leak
	delete i;
}