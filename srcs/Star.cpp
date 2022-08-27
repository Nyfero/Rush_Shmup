#include "Star.hpp"
#include <iostream>
//					//
//	Constructors	//
//					//

Star::Star(Game * gameptr) {
	game = gameptr;
	pos.x = game->getWidth();	// Responsive screen
	pos.y = rand() % game->getHeight() + 1;
	velocity = ((float)(rand() % 2 + 2 ) / 2) * -1; // -1 or -1.5
}

Star::~Star() {}

//				//
//	Functions	//
//				//

void	Star::update() {
	pos.x += velocity;
}

vec2i	Star::getPos() const {
	return (pos);
}

void 	Star::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, '.');
}

void 	Star::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}
