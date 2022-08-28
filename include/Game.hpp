#ifndef GAME_HPP
# define GAME_HPP


# include <ncurses.h>
# include <string>
# include <unistd.h>

# include "Utils.hpp"
# include "Player.hpp"
# include "Color.hpp"
# include "Bullet.hpp"

class Player;
class Bullet;

class Game
{
	public:

		Game();
		~Game();
		
		void	initColor( void );
		void	run( bool multiplayer );

		void	drawHud( Player & player );

		template< class Entites >
		bool	CheckCollision( Entites & entity, Bullet* b, int score);


		// void	checkCollision( void );
		operator bool() const;
		int_fast16_t	getWidth() const;
		int_fast16_t	getHeight() const;
		long			getTick() const;
		WINDOW*			getWin();

	private:
		WINDOW*		main_win;
		WINDOW*		game_win;
		rect		screen_size;
		rect		game_size;
		long		tick;
		// Space<Tana> tanas;
		// Space<Bullet> bullets;
		// Space<Star> stars;
		static int info_height;
		bool		loop;
		bool		_status;
		int			scores;
};

#endif
