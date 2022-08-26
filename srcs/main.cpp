#include <ncurses.h>
#include <string>
#include "Game.hpp"

int	main(int ac, char** av)
{
	(void) ac;
	(void) av;

	Game game;
	
	if (!game)
		return 1;

	game.run();

	return 0;
}
