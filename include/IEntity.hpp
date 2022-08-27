#ifndef IENTITY_HPP
# define IENTITY_HPP

# include "Game.hpp"

class IEntity
{
	public:
		//Destructor
		virtual ~IEntity() {}
		
		//Functions
		virtual void	update() = 0;
		virtual void	print() const = 0;
		virtual void	clear() = 0;
}

#endif
