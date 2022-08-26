#include "Game.hpp"
#include <stdlib.h>
#include <vector>



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
				if(lst.at(i).getPos().y > 100) // 100 max y
					lst.erase(lst.begin() + i);

				lst.at(i).update();
			}

			// spawn a new object
			Object s(rand() % 100, 0); // 100 max x
			lst.push_back(s);  
		};
		std::vector<Object> getData() const { return lst; };
	private:
		std::vector<Object>	lst;
};

Game::Game() : _status(false)
{
	srand(time(NULL));

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

	Objects stars;
	int	input;
	bool loop = true;
	while(loop)
	{
		input = wgetch(win);

		// Remove object from previous position
		for(Object s : stars.getData())
		{
			mvaddch(s.getPos().y, s.getPos().x, ' ');
		}

		stars.update();
		switch (input)
		{
			case 'Q':
			case 'q':
			case 27: // Escape key
				loop = false;
				break;
		}

		for(Object s : stars.getData())
		{
			// Displays given character at given position
			mvaddch(s.getPos().y, s.getPos().x, '.');
		}

		usleep(10000); // 10ms
		refresh();
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