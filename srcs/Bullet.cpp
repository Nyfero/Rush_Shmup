#include "Bullet.hpp"

//					//
//	Constructors	//
//					//

Bullet::Bullet(Game * gameptr, Source source, float velocity, int_fast16_t x, int_fast16_t y): _game(gameptr) {
	_source = source;
	_velocity = velocity;
	_pos.x = x;
	_pos.y = y;
}

Bullet::~Bullet() {}

//				//
//	Functions	//
//				//

void	Bullet::update() {
	_pos.x += _velocity;
}

vec2i	Bullet::getPos() const {
	return (_pos);
}

void 	Bullet::print() {
	mvwaddch(_game->getWin(), _pos.y, _pos.x, '-' | (_source == Source::SPlayer ? COLOR_PAIR(Color::Yellow) : COLOR_PAIR(Color::Red)) | A_BOLD);
}

void 	Bullet::clear() {
	mvwaddch(_game->getWin(), _pos.y, _pos.x, ' ');
}
