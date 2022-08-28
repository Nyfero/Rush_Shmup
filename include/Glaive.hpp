#ifndef GLAIVE_HPP
# define GLAIVE_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Glaive: public IEntity
{
	private:
		vec2i	pos;
		Game 	*game;
		int		life;
		int		velocity;

	public:
		//Constructors
		Glaive(Game *gameptr);
		~Glaive();

		//Functions
		void	update();
		void	print();
		void	clear();
		vec2i	getPos() const;
		void	hit();
		int		getLife() const;
};

#endif


	// <&&
 	//   &&
  	//    &&&
 	//   (X &&&~~
  	//    &&&
 	//   &&
	// <&&
