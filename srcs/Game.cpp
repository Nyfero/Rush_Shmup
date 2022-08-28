#include "Game.hpp"
#include "Star.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "Tana.hpp"
#include "Hurricane.hpp"
#include "Glaive.hpp"
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

	init_color(Color::CLightGray, r(74), r(72), r(72));
	init_color(Color::CLightGray2, r(100), r(100), r(100));
	init_color(Color::CGray, r(5), r(5), r(11));

	init_pair(Color::White, COLOR_WHITE, Color::CGray);
	init_pair(Color::Red, COLOR_RED, Color::CGray);
	init_pair(Color::Yellow, COLOR_YELLOW, Color::CGray);
	init_pair(Color::Green, COLOR_GREEN, Color::CGray);
	init_pair(Color::Blue, COLOR_BLUE, Color::CGray);
	init_pair(Color::CStar, Color::CLightGray, Color::CGray);
	init_pair(Color::CStar2, Color::CLightGray2, Color::CGray);
	init_pair(Color::Gray, COLOR_WHITE, Color::CGray);
	init_pair(Color::HP_1, COLOR_GREEN, COLOR_GREEN);
	
	screen_size = {{0, 0}, {80, 24}};
	game_size = {{0, 0}, {screen_size.width() - 2, screen_size.height() - info_height - 4}};
  
	main_win = newwin( screen_size.height(), screen_size.width(), 0, 0);
	game_win = newwin( screen_size.height() - info_height - 2, screen_size.width() - 2, screen_size.top() + 1, screen_size.left() + 1);

	keypad(main_win, true);
	keypad(game_win, true);
	
	nodelay(main_win, true);
	nodelay(game_win, true);
	wbkgd(stdscr, COLOR_PAIR(Color::Gray));
	wbkgd(main_win, COLOR_PAIR(Color::Gray));
	wbkgd(game_win, COLOR_PAIR(Color::Gray));
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

void	Game::drawHud( Player & player )
{
	werase(main_win);
	wattron(main_win, A_BOLD);
	box(main_win, 0, 0);
	wattroff(main_win, A_BOLD);
	wmove(main_win, game_size.bottom() + 3, 1);
	whline(main_win, '-', screen_size.width()- 2);
	mvwaddstr(main_win, screen_size.height()- 3, 2, "Health: ");
	for (int i = 0; i < player.getLife(); i++)
	{
		wattron(main_win, COLOR_PAIR(Color::HP_1));
		mvwaddstr(main_win, screen_size.height() - 3, 10 + i+2, "  ");
		wattroff(main_win, COLOR_PAIR(Color::HP_1)); 
	}
	
	std::string minute(std::to_string(tick/6000));
	if (minute[0] == '0')
		minute.clear();
	else
		minute.append("m");

	mvwprintw(main_win, screen_size.height()-3, 14+ MAX_HP*2, "Time: %s %ds", minute.c_str(), (tick/100)%60);
	wrefresh(main_win);
}

void	Game::run( void )
{
	Space<Star> 		stars(this);
	Space<Tana> 		tanas(this);
	Space<Hurricane>	hurricanes(this);
	Space<Bullet>		bullets(this);
	Space<Glaive>		glaives(this);
	
	Player		player(this);
	
	int	input;
	loop = true;
	int lock = 0;

	drawHud(player);
	wrefresh(game_win);
	
	tick = 0;
	while(loop || player.getLife() <= 0)
	{
		input = tolower(wgetch(main_win));

		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).clear();
		for (size_t i = 0; i < glaives.getData().size(); ++i)
			glaives.getData().at(i).clear();
		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).clear();
		for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			hurricanes.getData().at(i).clear();
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
				if (player.shoot())
					bullets.create(Source::SPlayer, 1.0f, player.getPos().x, player.getPos().y);
				break;
			case KEY_RESIZE:
				wresize(main_win, screen_size.height(), screen_size.width());
				break;
		}

		if (tick % 40 == 0)
		{
			glaives.update(player);
			player.reload();
		}

		if (tick % 4 == 0)
			bullets.update();

		Bullet	*b = NULL;
		for (size_t i = 0; i < bullets.getData().size(); ++i)
		{
			b = &bullets.getData().at(i);
			if (b == NULL)
				continue;
			//Check si balle player touche
			if (b->getSource() == Source::SPlayer)
			{
				for (size_t j = 0; j < hurricanes.getData().size(); ++j)
				{
					if (b->getPos() == hurricanes.getData().at(j).getPos())
					{
						hurricanes.remove(j);
						bullets.remove(i);
						b = NULL;
						break;
					}
				}
				if (b == NULL)
					continue;
				for (size_t j = 0; j < tanas.getData().size(); ++j)
				{
					if (b->getPos() == tanas.getData().at(j).getPos())
					{
						tanas.remove(j);
						bullets.remove(i);
						break;
					}
				}
			}
			//Check si balle ennemi touche
			else if (b->getPos() == player.getPos())
			{
				player.update();
				bullets.remove(i);
			}
			b = NULL;
		}
			
		if (tick % 5 == 0)
		{
			tanas.update(player);
		}
		// if (tick > 250 && tick % 200 == 0)
		// 	tanas.create();

		if (tick % 10 == 0)
		{
			hurricanes.update(player);
			for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			{
				if (tick % 50 == 0 && rand() % 2 == 0)
					bullets.create(Source::SEnnemy, -1.0f, hurricanes.getData().at(i).getPos().x, hurricanes.getData().at(i).getPos().y);
			}
		}
		// if (/*tick > 500 && */tick % 500 == 0)
		// 	hurricanes.create();

		if (lock == 0)
		{
			glaives.create();
			lock = 1;
		}
		if (lock == 0)
		{
			if (tick % 7 == 0)
				stars.update(player);
			if (tick % 10 == 0)
				stars.update(player);
			if (tick % 20 == 0)
				stars.create();
		}



		for (size_t i = 0; i < bullets.getData().size(); ++i)
			bullets.getData().at(i).print();
		for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			hurricanes.getData().at(i).print();
		for (size_t i = 0; i < glaives.getData().size(); ++i)
			glaives.getData().at(i).print();
		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).print();
		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).print();

		player.disp(tick);

		
		drawHud(player);
		wrefresh(game_win);

		++tick;
		usleep(10000); // 10ms
	}
}

// void	Game::checkCollision() {
// 	for (size_t i = 0; i < bullets.getData().size(); ++i)
// 	{
// 		Bullet	*b = &bullets.getData().at(i);
// 
// 		//Check si balle player touche
// 		if (bullets.getData().at(i).getSource() == Source::SPlayer)
// 		{
// 			for (size_t j = 0; j < hurricanes.getData().size(); ++j)
// 			{
// 				if (bullets.getData().at(i).getPos() == hurricanes.getData().at(j).getPos())
// 				{
// 					hurricanes.getData().at(j).clear();
// 					hurricanes.getData().erase(j);
// 					bullets.getData().at(i).clear();
// 					bullets.getData().erase(i);
// 					b = NULL;
// 				}
// 			}
// 			for (size_t j = 0; b != NULL && j < tanas.getData().size(); ++j)
// 			{
// 				if (bullets.getData().at(i).getPos() == tanas.getData().at(j).getPos())
// 				{
// 					tanas.getData().at(j).clear();
// 					tanas.getData().erase(j);
// 					bullets.getData().at(i).clear();
// 					bullets.getData().erase(i);
// 				}
// 			}
// 		}
// 		//Check si balle ennemi touche
// 		else if (bullets.getData().at(i).getPos() == player.getPos())
// 		{
// 			player.update();
// 			bullets.getData().at(i).clear();
// 			bullets.getData().erase(i);
// 			if (player.getLife() == 0)
// 				_loop = false;
// 		}
// 	}
// }

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
