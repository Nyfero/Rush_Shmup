#include "Game.hpp"
#include "Star.hpp"
#include "Space.hpp"
#include "Player.hpp"
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
	Space<Bullet> bullets(this);
	
	Player		player(this);
	
	int	input;
	bool loop = true;

	wattron(main_win, A_BOLD);
	box(main_win, 0, 0);
	wattroff(main_win, A_BOLD);
	wmove(main_win, game_size.bottom() + 3, 1);
	whline(main_win, '-', screen_size.width()- 2);
	wrefresh(main_win);
	wrefresh(game_win);
	
	int nb_bullets = 20;
	tick = 0;
	while(loop)
	{
		input = tolower(wgetch(main_win));

		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).clear();
		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).clear();
		for (size_t i = 0; i < bullets.getData().size(); ++i)
			bullets.getData().at(i).clear();

		player.clear();

		switch (input)
		{
			case 'q':
			case 27: // Escape key
				loop = false;
				break;
			case KEY_LEFT:
			case 'a':
				if (player.getPos().x - 1 > 0)
					player.move(0);
				break;
			case KEY_RIGHT:
			case 'd':
				if (player.getPos().x + 1 < game_size.width())
					player.move(1);
				break;
			case KEY_UP:
			case 'w':
				if (player.getPos().y > 0)
					player.move(2);
				break;
			case KEY_DOWN:
			case 's':
				if (player.getPos().y <= game_size.height())
					player.move(3);
				break;
			case ' ':
				// if (nb_bullets > 0)
				// {
				// 	bullets.create(Source::SPlayer, 1.0f, x, y);
				// 	nb_bullets--;
				// }
				//shoot
				break;
			case 410:
				werase(main_win);
				werase(game_win);
				wattron(main_win, A_BOLD);
				box(main_win, 0, 0);
				wattroff(main_win, A_BOLD);
				wmove(main_win, game_size.bottom() + 3, 1);
				whline(main_win, '-', screen_size.width()- 2);
				break;
		}

		if (tick % 40 == 0)
		{
			if (nb_bullets < 10)
				nb_bullets++;
		}
		if (tick % 4 == 0)
			bullets.update();

		if (tick % 5 == 0)
			tanas.update();
		if (tick > 250 && tick % 30 == 0)
			tanas.create();

		if (tick % 7 == 0)
			stars.update();
		if (tick % 10 == 0)
			stars.create();


		for (size_t i = 0; i < bullets.getData().size(); ++i)
			bullets.getData().at(i).print();

		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).print();
		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).print();

		player.disp(tick);

		
		wrefresh(main_win);
		wrefresh(game_win);

		++tick;
		usleep(10000); // 1ms
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

long Game::getTick() const {
	return (tick);
}

WINDOW*			Game::getWin() {
	return (game_win);
}
