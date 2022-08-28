#include "Bullet.hpp"

//					//
//	Constructors	//
//					//

Bullet::Bullet(Game * gameptr, Source source, vec2i velocity, vec2i pos): _game(gameptr) {
	_source = source;
	_velocity.x = velocity.x;
	_velocity.y = velocity.y;
	_pos.x = pos.x;
	_pos.y = pos.y;
}

Bullet::~Bullet() {}

//				//
//	Functions	//
//				//

void	Bullet::update() {
	_pos.x += _velocity.x;
	_pos.y += _velocity.y;
}

vec2i	Bullet::getPos() const {
	return (_pos);
}


vec2i	Bullet::getVeloc() const {
	return (_velocity);
}

Source	Bullet::getSource() const {
	return (_source);
}

void 	Bullet::print() {
	mvwaddch(_game->getWin(), _pos.y, _pos.x, '-' | (_source == Source::SPlayer ? COLOR_PAIR(Color::Yellow) : COLOR_PAIR(Color::Red)) | A_BOLD);
}

void 	Bullet::clear() {
	mvwaddch(_game->getWin(), _pos.y, _pos.x, ' ');
}
