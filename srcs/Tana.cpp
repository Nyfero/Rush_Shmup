#include "Tana.hpp"
#include <time.h>

//					//
//	Constructors	//
//					//

Tana::Tana(Game *gameptr) { //Initialise un Tana qui avance en ligne droite
	game = gameptr;
	pos.x = game->getWidth();
	pos.y = rand() % game->getHeight() + 1;
	speed = Velocity(); 
}

Tana::~Tana() {}

//				//
//	Functions	//
//				//

float	Tana::Velocity() {
	srand(time(NULL));
	int		i = rand() % 100;
	float	x;

	if (i < 25) //Rapide
		x = -2;
	else //Normal
		x = -1;
	return (x);
}

void	Tana::update() {
	pos.x += speed;
}

void	Tana::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, 'T' | COLOR_PAIR(Color::Red));
}

void	Tana::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}

vec2i	Tana::getPos() const {
	return (pos);
}
