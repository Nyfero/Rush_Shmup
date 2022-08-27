#include "Tana.hpp"
#include <time.h>

//					//
//	Constructors	//
//					//

Tana::Tana(Game * gameptr): game(gameptr) {
	pos.x = game->getWidth();
	pos.y = rand() % game->getHeight() + 1;
	velocity = setVelocity();
}

Tana::~Tana() {}

//				//
//	Functions	//
//				//

vec2f	Tana::setVelocity() {
	vec2f	tmp;
	
	tmp.x = xVelocity();
	tmp.y = yVelocity();
	return (tmp);
}

void	Tana::update() {
	pos.x += velocity.x;
	pos.y += velocity.y;
}

void	Tana::print() {
	mvwaddch(game->getWin(), pos.y, pos.x, 'H' | COLOR_PAIR(Color::Red));
}

void	Tana::clear() {
	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
}

vec2i	Tana::getPos() const {
	return (pos);
}

float	Tana::xVelocity() {
	srand(time(NULL));
	int		i = rand() % 100;
	float	x;

	// if (pos.x <= (game->getWidth() / 3))
	// {
	// 	if (i < 50)	// 50% de chance en diagonale "droite"
	// 		x = 1;
	// 	else if (i >= 50 && i < 70) // 20% de chance en petite diagonale
	// 		x = 0.5;
	// 	else if (i >= 70 && i < 90) // 20% de chance en grosse diagonale
	// 		x = 2;
	// 	else // 10% de chance en ligne droite
	// 		x = 0;
	// }
	/*else*/ if (pos.x < ((2 * game->getWidth()) / 3))
	{
		if (i < 20)	// 20% de chance en diagonale "droite"
			x = 1;
		else if (i >= 20 && i < 40) // 20% de chance en diagonale inverse
			x = -1;
		else if (i >= 40 && i < 70) // 30% de chance en ligne droite
			x = 0;
		else if (i >= 70 && i < 85) // 15% de chance en petite diagonale
			x = 0.5;
		else	// 15% de chance en petite diagonale inverse
			x = -0.5;
	}
	else
	{
		if (i < 50)	// 50% de chance en diagonale "droite"
			x = -1;
		else if (i >= 50 && i < 70) // 20% de chance en petite diagonale
			x = -0.5;
		else if (i >= 70 && i < 90) // 20% de chance en grosse diagonale
			x = -2;
		else // 10% de chance en ligne droite
			x = 0;
	}
	return (x);
}

float 	Tana::yVelocity() {
	srand(time(NULL));
	int		i = rand() % 100;
	float	y;
	
	if (pos.y <= (game->getHeight() / 3))
	{
		if (i < 20) // 20% de chance en petite monte
			y = -0.5;
		else if (i >= 20 && i < 55) // 35% de chance en ligne droite
			y = 0;
		else if (i >= 55 && i < 80) // 25% de chance en petite descente
			y = 0.5;
		else // 20% de chance en grosse descente
			y = 1;
	}
	else if (pos.y > (game->getHeight() / 3) && pos.y < ((2 * game->getHeight()) / 3))
	{
		if (i < 20) // 20% de chance en grosse monte
			y = -1;
		else if (i >= 20 && i < 40) // 20% de chance en petite monte
			y = -0.5;
		else if (i >= 40 && i < 60) // 20% de chance en ligne droite
			y = 0;
		else if (i >= 60 && i < 80) // 20% de chance en petite descente
			y = 0.5;
		else // 20% de chance en grosse descente
			y = 1;
	}
	else
	{
		if (i < 20) // 20% de chance en petite descente
			y = 0.5;
		else if (i >= 20 && i < 55) // 35% de chance en ligne droite
			y = 0;
		else if (i >= 55 && i < 80) // 25% de chance en petite monte
			y = -0.5;
		else // 20% de chance en grosse monte
			y = -1;
	}
	return (y);
}
