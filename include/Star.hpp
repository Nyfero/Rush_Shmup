#ifndef STAR_HPP
# define STAR_HPP

# include "IEntity.hpp"
# include "Game.hpp" 

class Star: public IEntity
{
	private:
		vec2i	pos;
		float	velocity;
		Game	*game;

	public:
		//Constructors
		~Star();
		Star(Game *gameptr);
		
		//Functions
		vec2i	getPos() const;
		void	update();
		void	print();
		void	clear();
};

#endif
