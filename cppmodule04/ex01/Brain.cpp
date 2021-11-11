#include "Brain.hpp"

Brain::Brain()
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "";
}

Brain::~Brain()
{

}

Brain::Brain(Brain const &other)
{
	*this= other;
}

std::string const &Brain::getIdeas() const
{
	return (*this->ideas);
}

void Brain::addIdea(std::string idea)
{
	for (int i = 0; i < 100; i++)
	{
		if (this->ideas[i] == "")
		{
			this->ideas[i] = idea;
			break;
		}
	}
}

Brain &Brain::operator=(Brain const &other)
{
	for (int i = 0; i < 100; ++i)
	{
		this->ideas[i] = other.ideas[i];
	}
	return (*this);
}