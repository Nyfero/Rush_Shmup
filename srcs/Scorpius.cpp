#include "Scorpius.hpp"
#include "Game.hpp"

//					//
//	Constructors	//
//					//

Scorpius::Scorpius(Game *gameptr) {
	game = gameptr;
	pos.x = 66;
	pos.y = rand() % game->getHeight() + 2;
}

Scorpius::~Scorpius() {}

//				//
//	Functions	//
//				//

void	Scorpius::update() {
	int	i = rand() % 3;
	int	velocity;
	
	pos.x--;
	if (i == 0)
		velocity = -1;
	else if (i == 1)
		velocity = 0;
	else
		velocity = 1;
	if (pos.y + velocity < 0 || pos.y + velocity > game->getHeight() + 1)
		velocity *= -1;
	pos.y += velocity;
}

void	Scorpius::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, 'O' | COLOR_PAIR(Color::Red));
}

void	Scorpius::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}

vec2i	Scorpius::getPos() const {
	return (pos);
}
