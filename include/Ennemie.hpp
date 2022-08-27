#ifndef ENNEMIE_HPP
# define ENNEMIE_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Ennemie: public IEntity
{
	private:
		// const char	disp;
		vec2i		pos;
		// const bool	front = 1;
		vec2f		velocity;
		Game const&	game;
	
	public:
		//Constructors
		Ennemie(char c, int x, int y, Game const &game);
		~Ennemie();
		
		//Functions
		vec2f	setVelocity();
		float	xVelocity();
		float	yVelocity();
		void	update() = 0;
		void	print() const = 0;
		void	clear() = 0;
};

#endif
