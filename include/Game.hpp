#ifndef GAME_HPP
# define GAME_HPP

// # include "Objects"
# include <ncurses.h>
# include <string>
# include <unistd.h>
/*
uint8_t is guaranteed to be 8 bits
uint_fast8_t is guaranteed to be >= 8 bits, much like an unsigned char
*/
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2ui;

typedef struct {
    int_fast16_t x;
    int_fast16_t y;
} vec2i;

typedef struct s_rect{
	vec2i	offset;
	vec2i	bounds;

	int_fast16_t	top() { return offset.y; }
	int_fast16_t	bottom() { return offset.y + bounds.y; }
	int_fast16_t	left() { return offset.x; }
	int_fast16_t	right() { return offset.x + bounds.x; }

	int_fast16_t	width() { return bounds.x; }
	int_fast16_t	height() { return bounds.y; }

	bool			isIn(vec2i point) { return (point.x >= offset.x && point.x < right()) && (point.y >= offset.y && point.y < bottom());}

} rect;

class Game
{
	public:
		Game();
		~Game();
		
		void	run( void );
		operator bool() const;
	private:
		WINDOW*	main_win;
		WINDOW*	game_win;
		rect	screen_size;
		rect	game_size;
		// Objects	stars;
		// Objects	asteroids;

		bool	_status;
};

#endif