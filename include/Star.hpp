#ifndef STAR_HPP
# define STAR_HPP

# include "IEntity.hpp"
# include "Game.hpp" 

class Star: public IEntity
{
	private:
		vec2i	pos;
		float	velocity;

	public:
		//Constructors
		~Star();
		Star(Game &game);
		
		//Functions
		void	update();
		vec2i	getPos() const;
		void	print() const;
		void	clear() const;
};

#endif
