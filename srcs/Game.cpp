#include "Game.hpp"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>


class Object
{
	public:
		Object() {};
		Object(int x, int y, float vel) { pos.x = x; pos.y = y; velocity = vel;};
		~Object() {};
		void	update() {
			pos.x += velocity;
		};
		vec2i	getPos() const
		{
			return pos;
		};
	private:
		vec2i	pos;
		float velocity;
};

class Objects //Fields
{
	public:
		Objects() {};
		~Objects() {};
		void	update()
		{
			for (size_t i = 0; i < lst.size(); i++) {
				if (lst.at(i).getPos().x > 80 || lst.at(i).getPos().x < 0 ) // 100 max y
					lst.erase(lst.begin() + i);

				lst.at(i).update();
			}
		};
		void	create() {
			Object s(80, rand() % 24, ((float)(rand()%2+2)/2) * -1);
			lst.push_back(s);
		};
		std::vector<Object> getData() const { return lst; };
	private:
		std::vector<Object>	lst;
};

int Game::info_height = 4;

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

void	Game::run( void )
{
	Objects stars;

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
		for(Object s : stars.getData())
			mvwaddch(game_win, s.getPos().y, s.getPos().x, ' ');

		mvwaddch(game_win, y, x, ' ');
		mvwaddch(game_win, y, x-1, ' ');

		switch (input)
		{
			case 'q':
			case 27: // Escape key
				loop = false;
				break;
			case 'a':
				// if (ch == '<')
					x--;
				ch = '<';
				break;
			case 'd':
				// if (ch == '>')
					x++;
				ch = '>';
				break;
			case 'w':
				// if (ch == '^')
					y--;
				ch = '^';
				break;
			case 's':
				// if (ch == 'V')
					y++;
				ch = 'v';
				break;
			case ' ':

				break;
		}

		if (tick % 5 == 0)
			stars.update();
		if (tick % 17 == 0)
			stars.create();
		if ((tick % 15)/3)
			mvwaddch(game_win, y, x-1, '>' | COLOR_PAIR(tick%2 ? Color::Yellow : Color::Red));
		else
			mvwaddch(game_win , y, x-1, ' ');

		for(Object s : stars.getData())
			mvwaddch(game_win, (s.getPos().y), (s.getPos().x), '.');

		mvwaddch(game_win, y, x, '>' | COLOR_PAIR(Color::Blue));

		
		wrefresh(main_win);
		wrefresh(game_win);

		++tick;
		usleep(10000); // 10ms
	}
}
Game::operator bool() const
{
	return _status;
}

Game::~Game()
{
	endwin();
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