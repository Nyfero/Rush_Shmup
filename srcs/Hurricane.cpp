// #include "Hurricane.hpp"
// #include <time.h>
// 
// //					//
// //	Constructors	//
// //					//
// 
// Hurricane::Hurricane(Game *gameptr) {
// 	game = gameptr;
// 	pos.x = game->getWidth();
// 	pos.y = rand() % game->getHeight() + 1;
// 	velocity = setVelocity();
// }
// 
// Hurricane::~Hurricane() {}
// 
// //				//
// //	Functions	//
// //				//
// 
// vec2f	Hurricane::setVelocity() {
// 	vec2f	tmp;
// 
// 	tmp.x = xVelocity();
// 	tmp.y = yVelocity();
// 	return (tmp);
// }
// 
// void	Hurricane::update() {
// 	pos.x += velocity.x;
// 	pos.y += velocity.y;
// }
// 
// void	Hurricane::print() {
// 	mvwaddch(game->getWin(), pos.y, pos.x, 'H' | COLOR_PAIR(Game::Color::Red));
// }
// 
// void	Hurricane::clear() {
// 	mvwaddch(game->getWin(), pos.y, pos.x, ' ');
// }
// 
// vec2i	Hurricane::getPos() const {
// 	return (pos);
// }
// 
// float	Hurricane::xVelocity() {
// 	srand(time(NULL));
// 	int		i = rand() % 100;
// 	float	x;
// 
// 	if (i < 25) //Rapide
// 		x = -1.5;
// 	else if (i >= 25 && i < 50) //Normal +
// 		x = -1;
// 	else if (i >= 50 && i < 75) //Normal -
// 		x = -0.75;
// 	else //Lent
// 		x = -0.5;
// 	return (x);
// }
// 
// float 	Hurricane::yVelocity() {
// 	srand(time(NULL));
// 	int		i = rand() % 100;
// 	float	y;
// 
// 	if (pos.y <= (game->getHeight() / 3))
// 	{
// 		if (i < 20) // 20% de chance en petite monte
// 			y = -0.5;
// 		else if (i >= 20 && i < 55) // 35% de chance en ligne droite
// 			y = 0;
// 		else if (i >= 55 && i < 80) // 25% de chance en petite descente
// 			y = 0.5;
// 		else // 20% de chance en grosse descente
// 			y = 1;
// 	}
// 	else if (pos.y > (game->getHeight() / 3) && pos.y < ((2 * game->getHeight()) / 3))
// 	{
// 		if (i < 20) // 20% de chance en grosse monte
// 			y = -1;
// 		else if (i >= 20 && i < 40) // 20% de chance en petite monte
// 			y = -0.5;
// 		else if (i >= 40 && i < 60) // 20% de chance en ligne droite
// 			y = 0;
// 		else if (i >= 60 && i < 80) // 20% de chance en petite descente
// 			y = 0.5;
// 		else // 20% de chance en grosse descente
// 			y = 1;
// 	}
// 	else
// 	{
// 		if (i < 20) // 20% de chance en petite descente
// 			y = 0.5;
// 		else if (i >= 20 && i < 55) // 35% de chance en ligne droite
// 			y = 0;
// 		else if (i >= 55 && i < 80) // 25% de chance en petite monte
// 			y = -0.5;
// 		else // 20% de chance en grosse monte
// 			y = -1;
// 	}
// 	return (y);
// }
