#ifndef BULLET_HPP
# define BULLET_HPP

# include "IEntity.hpp"
# include "Game.hpp"



class Bullet: public IEntity
{
	private:
		vec2i	_pos;
		float	_velocity;
		Game *	_game;
		Source 	_source;
	public:
		//Constructors
		~Bullet();
		Bullet(Game * gameptr, Source source, float velocity, int_fast16_t x, int_fast16_t y);
		
		//Functions
		vec2i	getPos() const;
		float	getVeloc() const;
		Source	getSource() const;
		void	update();
		void	print();
		void	clear();
};

#endif
