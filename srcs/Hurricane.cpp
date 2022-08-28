#include "Hurricane.hpp"
#include <time.h>

//					//
//	Constructors	//
//					//

Hurricane::Hurricane(Game *gameptr) {
	game = gameptr;
	pos.x = game->getWidth();
	pos.y = rand() % (game->getHeight() + 2);
	velocity = yVelocity();
}

Hurricane::~Hurricane() {}

//				//
//	Functions	//
//				//

int	Hurricane::yVelocity() {
	srand(time(NULL));
	int		i = rand() % 100;
	
	if (i < 50)
		return (1);
	else 
		return (-1);
}

void	Hurricane::update() {
	pos.x--;
	if (pos.y + velocity < 0 || pos.y + velocity > game->getHeight() + 1)
		velocity *= -1;
	pos.y += velocity;
}

void	Hurricane::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, 'H' | COLOR_PAIR(Color::Green));
}

void	Hurricane::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}

vec2i	Hurricane::getPos() const {
	return (pos);
}

vec2i	Hurricane::getVeloc()
{
	return {-1, velocity};
}