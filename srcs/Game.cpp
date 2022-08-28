#include "Game.hpp"
#include "Star.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "Tana.hpp"
#include "Hurricane.hpp"
#include "Glaive.hpp"
#include "Scorpius.hpp"
#include "Bullet.hpp"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

//					//
//	Constructors	//
//					//

template< class Entites >
bool	Game::CheckCollision(Entites & entity, Bullet* b, int score)
{
	for (size_t j = 0; j < entity.getData().size(); ++j)
	{
		if (b->getPos() + b->getVeloc() == entity.getData().at(j).getPos()
		|| b->getPos() == entity.getData().at(j).getPos())
		{
			entity.remove(j);
			scores += score;
			return true;
		}
	}
	return false;
}

int	Game::info_height = 4;

void Game::initColor()
{
	start_color();

	init_color(Color::CLightGray, r(74), r(72), r(72));
	init_color(Color::CLightGray2, r(100), r(100), r(100));
	init_color(Color::CGray, r(5), r(5), r(11));
	init_color(Color::COrange, r(0xFF), r(0x7f), r(0x00));

	init_pair(Color::White, COLOR_WHITE, Color::CGray);
	init_pair(Color::Red, COLOR_RED, Color::CGray);
	init_pair(Color::Yellow, COLOR_YELLOW, Color::CGray);
	init_pair(Color::Green, COLOR_GREEN, Color::CGray);
	init_pair(Color::Blue, COLOR_BLUE, Color::CGray);
	init_pair(Color::CStar, Color::CLightGray, Color::CGray);
	init_pair(Color::CStar2, Color::CLightGray2, Color::CGray);
	init_pair(Color::Gray, COLOR_WHITE, Color::CGray);
	init_pair(Color::Purple, COLOR_MAGENTA, Color::CGray);
	init_pair(Color::Orange, Color::COrange, Color::CGray);

	init_pair(Color::CHP, COLOR_GREEN, COLOR_GREEN);
	init_pair(Color::CBullet, Color::COrange, Color::COrange);
	
}

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

	initColor();

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
	std::cout << "\n\
	\e[44;37m███████ ██ ███    ██ ██ ███████ ██   ██     ██\e[0m\n\
	\e[44;37m██      ██ ████   ██ ██ ██      ██   ██     ██\e[0m\n\
	\e[44;37m█████   ██ ██ ██  ██ ██ ███████ ███████     ██\e[0m\n\
	\e[44;37m██      ██ ██  ██ ██ ██      ██ ██   ██       \e[0m\n\
	\e[44;37m██      ██ ██   ████ ██ ███████ ██   ██     ██\e[0m\n\
\n\nYou have a scores of " << scores << "\nIn " << tick/6000 <<"m " << (tick/100)%60 << "s\n";
}

//				//
//	Functions	//
//				//

void	Game::drawHud( Player & player )
{
	unsigned long cursor = 2;
	werase(main_win);
	wattron(main_win, A_BOLD);
	box(main_win, 0, 0);
	wattroff(main_win, A_BOLD);
	wmove(main_win, game_size.bottom() + 3, 1);
	whline(main_win, '-', screen_size.width()- 2);

	mvwaddstr(main_win, screen_size.height()- 3, cursor, "Health: ");
	cursor += 9;
	for (int i = 0; i < player.getLife(); i++)
		mvwaddch(main_win, screen_size.height() - 3, cursor + (i*2), ' ' | COLOR_PAIR(Color::CHP));

	cursor += 3 + (Player::maxLife*2);
	
	mvwaddstr(main_win, screen_size.height()- 3, cursor, "Ammos: ");
	cursor += 7;
	for (int i = 0; i < player.getAmmo(); i++)
		mvwaddch(main_win, screen_size.height() - 3, cursor + i*2, ' ' | COLOR_PAIR(Color::CBullet));
	cursor += player.getAmmo()*2 + 2;

	
	std::string scoresStr(" Scores: ");
	if (scores > 1000)
	{
		scoresStr += std::to_string(scores/1000);
		scoresStr += "K";
	}
	else
		scoresStr += std::to_string(scores);
	cursor = screen_size.width()-(scoresStr.length());
	
	mvwaddstr(main_win, screen_size.height()- 3, cursor, scoresStr.c_str());

	std::string minute(std::to_string(tick/6000));
	if (minute[0] == '0')
		minute.clear();
	else
		minute.append("m");
	cursor -= std::snprintf( nullptr, 0, "Time: %s %lds ", minute.c_str(), (tick/100)%60 ) + 1;
	mvwprintw(main_win, screen_size.height()-3, cursor, "Time: %s %lds", minute.c_str(), (tick/100)%60);

	wrefresh(main_win);
}

void	Game::run( bool multiplayer )
{
	Space<Star> 		stars(this);
	Space<Tana> 		tanas(this);
	Space<Hurricane>	hurricanes(this);
	Space<Bullet>		bullets(this);
	Space<Scorpius>		scorpius(this);
	
	if (multiplayer)
		Player::maxLife = 6;
	Player		player(this);
	Player		player2(this, Color::Purple);

	Glaive		glaives(this);
	
	int	input;
	loop = true;
	int boss = 0;

	tick = 0;
	scores = 0;
	drawHud(player);
	wrefresh(game_win);
	
	while(player.getLife() > 0 && loop == true)
	{
		input = tolower(wgetch(main_win));

		/*	CLEAR ALL ENTITY	*/

		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).clear();
		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).clear();
		for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			hurricanes.getData().at(i).clear();
		for (size_t i = 0; i < bullets.getData().size(); ++i)
			bullets.getData().at(i).clear();
		for (size_t i = 0; i < scorpius.getData().size(); ++i)
			scorpius.getData().at(i).clear();

		player.clear();
		if (multiplayer)
			player2.clear();
		glaives.clear();

		/*	--------------------------------------------	*/
		
		/*	PLAYER INPUT	*/
		
		switch (input)
		{
			case 'q':
			case 27: // Escape key
				loop = false;
				break;
			
			case KEY_LEFT:
			if (multiplayer)
			{
				if (player2.getPos().x - 1 > 0)
					player2.move(0);
				break;
			}
			case 'a':
				if (player.getPos().x - 1 > 0)
					player.move(0);
				break;
			case KEY_RIGHT:
			if (multiplayer)
			{
				if (player2.getPos().x + 1 < game_size.width())
					player2.move(1);
				break;
			}
			case 'd':
				if (player.getPos().x + 1 < game_size.width())
					player.move(1);
				break;
			case KEY_UP:
			if (multiplayer)
			{
				if (player2.getPos().y > 0)
					player2.move(2);
				break;
			}
			case 'w':
				if (player.getPos().y > 0)
					player.move(2);
				break;
			case KEY_DOWN:
			if (multiplayer)
			{
				if (player2.getPos().y <= game_size.height())
					player2.move(3);
				break;
			}
			case 's':
				if (player.getPos().y <= game_size.height())
					player.move(3);
				break;
			case ' ':
				if (player.shoot())
					bullets.create(Source::SPlayer, {1, 0}, player.getPos());
				break;
			case '0':
			if (multiplayer)
			{
				if (player.shoot())
					bullets.create(Source::SPlayer, {1, 0}, player2.getPos());
				break;
			}
			case KEY_RESIZE:
				wresize(main_win, screen_size.height(), screen_size.width());
				break;
		}
		
		/*	--------------------------------------------------	*/
		
		/*	UPDATE BULLET AND CHECK COLLISION	*/
		

		
		Bullet	*b = NULL;
		for (size_t i = 0; i < bullets.getData().size(); ++i)
		{
			b = &bullets.getData().at(i);
			if (b == NULL)
				continue;
			//Check si balle player touche
			if (b->getSource() == Source::SPlayer)
			{
				if (CheckCollision<Space<Tana> >(tanas, b, 10)
				|| CheckCollision<Space<Hurricane> >(hurricanes, b, 15)
				|| CheckCollision<Space<Scorpius> >(scorpius, b, 30))
					bullets.remove(i);
				else if (b->getPos() == glaives.getPos())
				{
					glaives.hit();
					if (glaives.getLife() <= 0)
					{
						scores += 1000;
						glaives.clear();
					}
					bullets.remove(i);
				}
			}
			else {
				//Check si balle ennemi touche
				if (b->getPos() == player.getPos() ||
						b->getPos() + b->getVeloc() == player.getPos())
				{
					player.update();
					bullets.remove(i);
				}
				else if (b->getPos() == player2.getPos() ||
						b->getPos() + b->getVeloc() == player2.getPos())
				{
					player.update();
					bullets.remove(i);
				}
			}
			b = NULL;
		}
		
		if (tick % 2 == 0)
			bullets.update(Source::SPlayer);
		if (tick % 3 == 0)
			bullets.update(Source::SEnnemy);

		/*	--------------------------------------------	*/
		
		/*	UPDATE ALL ENTITY	*/

		//	update player bullets
		if (tick % (multiplayer?20:40) == 0)
			player.reload();
		
		//	update stars
		if (boss == 0)
		{
			if (tick % 7 == 0)
				stars.update(player, multiplayer? &player2 : NULL);
			if (tick % 10 == 0)
				stars.update(player, multiplayer? &player2 : NULL);
			if (tick % 20 == 0)
			stars.create();
		}
		
		//	update tanas
		if (tick % 5 == 0)
			tanas.update(player, multiplayer? &player2 : NULL);
		if (tick > 500 && tick % 200 == 0 && boss == 0)
			tanas.create();
		if (tick > 1 && tick % 3000 == 0 && boss == 0)
		{
			tanas.create();
			tanas.create();
			tanas.create();
			tanas.create();
			tanas.create();
		}
		if (tick > 1 && tick % 12000 == 0 && boss == 0)
		{
			tanas.create();
			tanas.create();
			tanas.create();
		}
		
		//	update hurricanes
		if (tick % 10 == 0)
		{
			hurricanes.update(player, multiplayer? &player2 : NULL);
			for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			{
				if (tick % 50 == 0 && rand() % 2 == 0)
				bullets.create(Source::SEnnemy, {-1, 0} , hurricanes.getData().at(i).getPos());
			}
		}
		if (tick > 1500 && tick % 500 == 0 && boss == 0)
			hurricanes.create();
		if (tick > 1 && tick % 6000 == 0 && boss == 0)
		{
			hurricanes.create();
			hurricanes.create();
			hurricanes.create();
		}
		
		//	update scorpius
		if (tick % 20 == 0 && boss == 1)
		{
			scorpius.update(player, multiplayer? &player2 : NULL);
			for (size_t i = 0; i < scorpius.getData().size(); ++i)
			{
				if (tick % 125 == 0)
				{
					bullets.create(Source::SEnnemy, {-1, 1} , scorpius.getData().at(i).getPos());
					bullets.create(Source::SEnnemy, {-1, -1} , scorpius.getData().at(i).getPos());
					bullets.create(Source::SEnnemy, {-1, 0} , scorpius.getData().at(i).getPos());
					bullets.create(Source::SEnnemy, {1, 1} , scorpius.getData().at(i).getPos());
					bullets.create(Source::SEnnemy, {1, -1} , scorpius.getData().at(i).getPos());
					bullets.create(Source::SEnnemy, {1, 0} , scorpius.getData().at(i).getPos());
				}
			}
		}
		if (boss == 1)
			if (tick % 300 == 0)
				scorpius.create();	
		if (glaives.getLife() < 0 && tick % 500 == 0)
			scorpius.create();

		//	update glaives
		if (boss == 1 && tick % 50 == 0)
		{
			glaives.update();
			if (tick % 100 == 0)
			{
				bullets.create(Source::SEnnemy, {-1, 0} , glaives.getUpWeapon());
				bullets.create(Source::SEnnemy, {-1, 0} , glaives.getDownWeapon());
			}
			if (tick % 300 == 0)
			{
				bullets.create(Source::SEnnemy, {-1, 1} , glaives.getUpWeapon());
				bullets.create(Source::SEnnemy, {-1, 1} , glaives.getDownWeapon());
				bullets.create(Source::SEnnemy, {-1, -1} , glaives.getUpWeapon());
				bullets.create(Source::SEnnemy, {-1, -1} , glaives.getDownWeapon());
				bullets.create(Source::SEnnemy, {-1, 0} , glaives.getPos());
				bullets.create(Source::SEnnemy, {-1, 1} , glaives.getPos());
				bullets.create(Source::SEnnemy, {-1, -1} , glaives.getPos());
			}
		}
		if (tick > 1 && tick % 15000 == 0)
		{
			boss = 1;
			if (glaives.getLife() <= 0)
				glaives.heal();
		}
				
		/*	PRINT ALL ENTITY	*/

		for (size_t i = 0; i < stars.getData().size(); ++i)
			stars.getData().at(i).print();
		for (size_t i = 0; i < bullets.getData().size(); ++i)
			bullets.getData().at(i).print();
		for (size_t i = 0; i < tanas.getData().size(); ++i)
			tanas.getData().at(i).print();
		for (size_t i = 0; i < hurricanes.getData().size(); ++i)
			hurricanes.getData().at(i).print();
		if (boss == 1)
			for (size_t i = 0; i < scorpius.getData().size(); ++i)
				scorpius.getData().at(i).print();

		if (boss == 1)
		{
			if (glaives.getLife() > 0)
				glaives.print();
			else
			{
				boss = 0;
				player.heal();
			}
		}
		player.disp(tick);
		if (multiplayer)
			player2.disp(tick);

		/*	---------------------------------------------	*/
		
		drawHud(player);
		wrefresh(game_win);

		++tick;
		usleep(9500);
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
