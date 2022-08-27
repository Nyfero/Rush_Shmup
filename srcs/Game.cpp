#include "Game.hpp"
#include "Star.hpp"
#include "Space.hpp"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

//					//
//	Constructors	//
//					//

int	Game::info_height = 4;

Game::Game() : _status(false)
{
	srand(time(NULL));
	
	main_win = initscr();
	if (!main_win)
	return ;
	cbreak(); // Wait key not line ?
	noecho(); // No print key on press
	clear();
	refresh();

	curs_set(0); // Remove cursor
	
	if(!has_colors()) {
		endwin();
		printf("ERROR: Terminal does not support color.\n");
		exit(1);
	}
	start_color();

	init_pair(Color::White, COLOR_WHITE, COLOR_BLACK);
	init_pair(Color::Red, COLOR_RED, COLOR_BLACK);
	init_pair(Color::Yellow, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Color::Green, COLOR_GREEN, COLOR_BLACK);
	init_pair(Color::Blue, COLOR_BLUE, COLOR_BLACK);
	screen_size = {{0, 0}, {80, 24}};
	game_size = {{0, 0}, {screen_size.width() - 2, screen_size.height() - info_height - 4}};
  
	main_win = newwin( screen_size.height(), screen_size.width(), 0, 0);
	game_win = newwin( screen_size.height() - info_height - 2, screen_size.width() - 2, screen_size.top() + 1, screen_size.left() + 1);

	keypad(main_win, true);
	keypad(game_win, true);
	
	nodelay(main_win, true);
	nodelay(game_win, true);
	bkgd(COLOR_PAIR(1));
	refresh();

	_status = true;
}

Game::~Game() {
	endwin();
}

//				//
//	Functions	//
//				//


void	Game::run( void )
{
	Space<Star> space(*this);

	int	input;
	bool loop = true;
	int x = 0;
	int y = 0;
	char ch = '^';

	wattron(main_win, A_BOLD);
	box(main_win, 0, 0);
	wattroff(main_win, A_BOLD);
	wmove(main_win, game_size.bottom() + 3, 1);
	whline(main_win, '-', screen_size.width()- 2);
	wrefresh(main_win);
	wrefresh(game_win);

	tick = 0;
	while(loop)
	{
		input = tolower(wgetch(main_win));

		// Remove object from previous position
		for (size_t i = 0; i < space.getData().size(); ++i)
		{
			Star s = space.getData().at(i);
			mvwaddch(game_win, s.getPos().y, s.getPos().x, ' ');
		}

		mvwaddch(game_win, y, x, ' ');
		mvwaddch(game_win, y, x-1, ' ');

		switch (input)
		{
			case 'q':
			case 27: // Escape key
				loop = false;
				break;
			case KEY_LEFT:
			case 'a':
				// if (ch == '<')
					x--;
				ch = '<';
				break;
			case KEY_RIGHT:
			case 'd':
				// if (ch == '>')
					x++;
				ch = '>';
				break;
			case KEY_UP:
			case 'w':
				// if (ch == '^')
					y--;
				ch = '^';
				break;
			case KEY_DOWN:
			case 's':
				// if (ch == 'V')
					y++;
				ch = 'v';
				break;
			case ' ':

				break;
		}

		if (tick % 5 == 0)
			space.update();
		if (tick % 17 == 0)
			space.create();
		if ((tick % 15)/3)
			mvwaddch(game_win, y, x-1, '>' | COLOR_PAIR(tick%2 ? Color::Yellow : Color::Red));
		else
			mvwaddch(game_win , y, x-1, ' ');

		for(Star s : space.getData())
			s.print();

		mvwaddch(game_win, y, x, '>' | COLOR_PAIR(Color::Blue));

		
		wrefresh(main_win);
		wrefresh(game_win);

		++tick;
		usleep(10000); // 10ms
	}
}

Game::operator bool() const {
	return (_status);
}

int_fast16_t Game::getWidth() const {
	return (game_size.width());
}

int_fast16_t Game::getHeight() const {
	return (game_size.height());
}

long Game::getTick() const
{
	return tick;
}