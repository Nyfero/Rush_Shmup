#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>
# include <unistd.h>
/*
uint8_t is guaranteed to be 8 bits
uint_fast8_t is guaranteed to be >= 8 bits, much like an unsigned char
*/
typedef struct {
    uint_fast8_t x;
    uint_fast8_t y;
} vec2ui;

typedef struct {
    int_fast8_t x;
    int_fast8_t y;
} vec2i;

class Game
{
	public:
		Game();
		~Game();
		
		void	run( void );
		operator bool() const;
	private:
		WINDOW*	win;
		bool	_status;
};

#endif


		Y = 0
X = 0	---------
		|		|
		|		|
		|		|
		|		|
		_________
