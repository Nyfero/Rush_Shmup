#include "Star.hpp"

//					//
//	Constructors	//
//					//

Star::Star(Game * gameptr): game(gameptr) {
	pos.x = game->getWidth();	// Responsive screen
	pos.y = rand() % (game->getHeight()+2);
	velocity = ((float)(rand() % 2 + 2 ) / 2) * -1; // -1 or -1.5
	color = rand() % 2 ? Color::CStar2 : Color::CStar;
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

vec2i	Star::getVeloc() {
	return {0, 0};
}

void 	Star::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, '.' | COLOR_PAIR(color));
}

void 	Star::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}
