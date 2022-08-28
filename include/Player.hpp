#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "IEntity.hpp"
# include "Game.hpp"
# include "Color.hpp"

class Game;

class Player: public IEntity
{
	private:
		vec2i	pos;
		int		life;
		int		bullets;
		Game	*game;
		Color	color;
		
		static int maxAmmos;

	public:
		static int maxLife;

		//Constructors
		Player(Game *gameptr);
		Player(Game *gameptr, Color color);
		~Player();

		//Functions
		vec2i	getPos() const;
		int		getLife() const;
		int		getAmmo() const;
		void	update();
		void	move(int dir);
		void	print();
		void	disp(int tick);
		void	clear();
		void	reload();
		int		shoot();
};

#endif
