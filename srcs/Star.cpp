#include "Star.hpp"

//					//
//	Constructors	//
//					//

Star::Star(Game const &game) {
	pos.x = game.getWidth();
	pos.y = rand() % game.getHeight();
	velocity = ((float)(rand()%2+2)/2) * -1;
}

Star::~Star() {}

void	Star::update() {
	pos.x += velocity;
}

vec2i	getPos() const {
	return (pos);
}
