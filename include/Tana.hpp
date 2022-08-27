#ifndef TANA_HPP
# define TANA_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Tana: public IEntity
{
	private:
		vec2i		pos;
		// const bool	front = 1;
		vec2f		velocity;
		Game *		game;
	
	public:
		//Constructors
		Tana(Game * gameptr);
		~Tana();
		
		//Functions
		vec2i	getPos() const;
		vec2f	setVelocity();
		float	xVelocity();
		float	yVelocity();
		void	update();
		void	print();
		void	clear();
};

#endif
