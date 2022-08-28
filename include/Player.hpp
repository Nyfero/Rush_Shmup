#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "IEntity.hpp"
# include "Game.hpp" 

class Player: public IEntity
{
	private:
		vec2i	pos;
		int		life;
		int		bullets;
		Game	*game;

	public:
		//Constructors
		Player(Game *gameptr);
		~Player();
		
		//Functions
		vec2i	getPos() const;
		int		getLife() const;
		void	update();
		void	move(int dir);
		void	print();
		void	disp(int tick);
		void	clear();
		void	reload();
		int		shoot();
};

#endif
