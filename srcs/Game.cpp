#include "Game.hpp"
#include "Star.hpp"
#include "Space.hpp"
#include "Tana.hpp"
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
	delwin(main_win);
	delwin(game_win);
	endwin();
}

//				//
//	Functions	//
//				//


void	Game::run( void )
{
	Space<Star> stars(this);
	Space<Tana> tanas(this);

	move(5, 5);

	std::string text = "Hello world!";
	addstr(text.c_str());

	Space<Star>	space(this);
	Space<Tana>	tana(this);
	int	input;
	bool loop = true;
	int x = game_size.width()/4;
	int y = game_size.height()/2;
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

		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).clear();
		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).clear();

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
				if (x-1 > 0)
					x--;
				ch = '<';
				break;
			case KEY_RIGHT:
			case 'd':
				if (x+1 < game_size.width())
					x++;
				ch = '>';
				break;
			case KEY_UP:
			case 'w':
				if (y > 0)
					y--;
				ch = '^';
				break;
			case KEY_DOWN:
			case 's':
				if (y <= game_size.height())
					y++;
				ch = 'v';
				break;
			case ' ':

				break;
		}

		if (tick % 5 == 0)
			tanas.update();
		if (tick > 1 && tick % 30 == 0)
			tanas.create();

		if (tick % 5 == 0)
			stars.update();
		if (tick % 17 == 0)
			stars.create();
		if ((tick % 15)/3)
			mvwaddch(game_win, y, x-1, '>' | COLOR_PAIR(tick%2 ? Color::Yellow : Color::Red));
		else
			mvwaddch(game_win , y, x-1, ' ');

		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).print();
		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).print();

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

WINDOW*			Game::getWin()
{
	return game_win;
}
