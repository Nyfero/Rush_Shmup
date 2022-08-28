#ifndef SCORPIUS_HPP
# define SCORPIUS_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Scorpius: public IEntity
{
	private:
		vec2i	pos;
		Game 	*game;
		int		velocity;

	public:
		//Constructors
		Scorpius(Game *gameptr);
		~Scorpius();

		//Functions
		vec2i	getVeloc();
		void	update();
		void	print();
		void	clear();
		vec2i	getPos() const;
};

#endif
