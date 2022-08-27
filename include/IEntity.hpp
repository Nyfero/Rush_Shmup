#ifndef IENTITY_HPP
# define IENTITY_HPP

# define PI 3.1415
# include "Game.hpp"

class IEntity
{
	public:
		//Destructor
		virtual ~IEntity() {}
		
		//Functions
		virtual void	update() = 0;
		virtual void	clear() = 0;
		virtual void	print() = 0;
};

#endif
