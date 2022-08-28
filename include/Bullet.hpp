#ifndef BULLET_HPP
# define BULLET_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Game;

class Bullet: public IEntity
{
	private:
		vec2i	_pos;
		vec2i	_velocity;
		Game *	_game;
		Source 	_source;
	public:
		//Constructors
		~Bullet();
		Bullet(Game * gameptr, Source source, vec2i velocity, vec2i pos);
		
		//Functions
		vec2i	getPos() const;
		vec2i	getVeloc() const;
		Source	getSource() const;
		void	update();
		void	print();
		void	clear();
};

#endif
