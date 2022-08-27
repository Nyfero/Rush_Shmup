#include "Game.hpp"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>


class Object
{
	public:
		Object() {};
		Object(int x, int y) { pos.x = x; pos.y = y; };
		~Object() {};
		void	update() {
			++pos.y;
		};
		vec2i	getPos() const
		{
			return pos;
		};
	private:
		vec2i	pos;
};

class Objects
{
	public:
		Objects() {};
		~Objects() {};
		void	update()
		{
			for(size_t i = 0; i < lst.size(); i++) {
				if(lst.at(i).getPos().y > 24) // 100 max y
					lst.erase(lst.begin() + i);

				lst.at(i).update();
			}

			// spawn a new object
			Object s(rand() % 80, 0); // 100 max x
			lst.push_back(s);  
		};
		std::vector<Object> getData() const { return lst; };
	private:
		std::vector<Object>	lst;
};
/*
	if(lst.at(i).getPos().x > 80 || lst.at(i).getPos().x < 0 ) // 100 max y
		void	create() {
			Object s(80, rand() % 24, ((float)(rand()%2+2)/2));
			lst.push_back(s);
		};
*/

Game::Game() : _status(false)
{
	srand(time(NULL));

	main_win = initscr();
	if (!main_win)
		return ;
	cbreak(); // Wait key not line ?
	noecho(); // No print key on press
	keypad(main_win, true); // Can use arrow key
	nodelay(main_win, true); // Remove the wait key with getch
	curs_set(0); // Remove cursor
	clear();
	
	if(!has_colors()) {
		endwin();
		printf("ERROR: Terminal does not support color.\n");
		exit(1);
	}
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK); // Create a color with id 1 with black back and blue front
	init_pair(2, COLOR_RED, COLOR_BLACK); // Create a color with id 1 with black back and blue front
	wbkgd(main_win, COLOR_PAIR(1)); // set color with id 1


	screen_size = {{0, 0}, {80, 24}};
	_status = true;
}

void	Game::run( void )
{
	uint_least16_t maxx, maxy;
	getmaxyx(main_win, maxy, maxx);
	(void)game_win;
	(void)screen_size;
	(void)game_size;
	attron(A_BOLD); // Atribute Bold on
	box(main_win, 0, 0); // Create a box
	attroff(A_BOLD); // Atribute Bold off

	move(5, 5);

	std::string text = "Hello world!";
	addstr(text.c_str());

	Objects stars;
	int	input;
	bool loop = true;
	int x = 0;
	int y = 0;
	char ch = '^';
	int tick = 0;
		erase();
	while(loop)
	{
		input = wgetch(main_win);

		// Remove object from previous position
		for(Object s : stars.getData())
		{
			mvaddch(s.getPos().y, s.getPos().x, ' ');
		}


		attron(COLOR_PAIR(2));
		mvaddch(y, x, ' ');
		mvaddch(y, x-1, ' ');
		attroff(COLOR_PAIR(2));


		switch (input)
		{
			case 'Q':
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
				ch = ACS_UARROW;
				break;
			case 's':
				// if (ch == 'V')
					y++;
				ch = ACS_DARROW;
				break;
			case ' ':

				break;
		}

		if (tick % 5 == 0)
			stars.update();
		if (tick % 17 == 0)
			stars.create();
		if ((tick % 10)/3)
		{
			attron(COLOR_PAIR(2));
			mvaddch(y, x-1, '>');
			attroff(COLOR_PAIR(2));
		}


		for(Object s : stars.getData())
		{
			mvaddch((s.getPos().y), (s.getPos().x), '.');
		}
		attron(A_BOLD); // Atribute Bold on
		mvaddch(y, x, '@');
		attroff(A_BOLD); // Atribute Bold off

		refresh();
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