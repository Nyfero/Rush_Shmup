#ifndef ENNEMIE_HPP
# define ENNEMIE_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Tana: public IEntity
{
	private:
		const char	disp = 'H';
		vec2i		pos;
		// const bool	front = 1;
		vec2f		velocity;
		Game const&	game;
	
	public:
		//Constructors
		Tana(Game const &game);
		~Tana();
		
		//Functions
		vec2f	setVelocity();
		float	xVelocity();
		float	yVelocity();
		void	update();
		void	print() const;
		void	clear() const;
};

#endif
