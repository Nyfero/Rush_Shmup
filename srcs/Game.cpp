#include "Game.hpp"
#include <stdlib.h>

Game::Game() : _status(false)
{
	win = initscr();
	if (!win)
		return ;
	cbreak(); // Wait key not line ?
	noecho(); // No print key on press
	keypad(win, true); // Can use arrow key
	nodelay(win, true); // Remove the wait key with getch
	curs_set(0); // Remove cursor
	clear();
	
	if(!has_colors()) {
		endwin();
		printf("ERROR: Terminal does not support color.\n");
		exit(1);
	}
	start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLACK); // Create a color with id 1 with black back and blue front
    wbkgd(win, COLOR_PAIR(1)); // set color with id 1

	_status = true;
}

void	Game::run( void )
{
    attron(A_BOLD); // Atribute Bold on
    box(win, 0, 0); // Create a box
    attroff(A_BOLD); // Atribute Bold off

	move(5, 5);

	std::string text = "Hello world!";
	addstr(text.c_str());

	refresh();

	while(1);
}
Game::operator bool() const
{
	return _status;
}

Game::~Game()
{
	endwin();
}