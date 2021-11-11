#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <string>

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		~Brain();
		Brain(Brain const &other);
		std::string const &getIdeas() const;
		void addIdea(std::string idea);
		Brain &operator=(Brain const &other);
};



#endif