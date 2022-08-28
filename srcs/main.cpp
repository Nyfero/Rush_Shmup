#include <ncurses.h>
#include <string>
#include "Game.hpp"

int	main(int ac, char** av)
{
	bool multiplayer = false;
	if (ac > 1)
	{
		std::string option(av[1]);
		if (option == "--multiplayer" || option == "-m")
			multiplayer = true;
	}
	Game game;
	
	if (!game)
		return 1;

	game.run(multiplayer);

	return 0;
}
