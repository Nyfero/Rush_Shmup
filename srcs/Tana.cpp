#include "Tana.hpp"
#include <time.h>

//					//
//	Constructors	//
//					//

Tana::Tana(Game *gameptr) { //Initialise un Tana qui avance en ligne droite
	game = gameptr;
	pos.x = game->getWidth();
	pos.y = rand() % (game->getHeight() + 2);
}

Tana::~Tana() {}

//				//
//	Functions	//
//				//


void	Tana::update() {
	pos.x--;
}

void	Tana::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, 'T' | COLOR_PAIR(Color::Red));
}
vec2i	Tana::getVeloc()
{
	return {-1, 0};
}

void	Tana::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}

vec2i	Tana::getPos() const {
	return (pos);
}
