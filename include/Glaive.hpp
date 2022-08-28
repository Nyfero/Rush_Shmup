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
		vec2i	getUpWeapon() const;
		vec2i	getDownWeapon() const;
		void	heal();
};

#endif


	// <&&
 	//   &&
  	//    &&&
 	//   (X &&&~~
  	//    &&&
 	//   &&
	// <&&
