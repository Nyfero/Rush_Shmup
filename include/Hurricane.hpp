// #ifndef HURRICANE_HPP
// # define HURRICANE_HPP
// 
// # include "IEntity.hpp"
// # include "Game.hpp"
// 
// class Hurricane: public IEntity
// {
// 	private:
// 		vec2i	pos;
// 		vec2f	velocity;
// 		Game 	*game;
// 
// 	public:
// 		//Constructors
// 		Hurricane(Game *gameptr);
// 		~Hurricane();
// 
// 		//Functions
// 		vec2f	setVelocity();
// 		float	xVelocity();
// 		float	yVelocity();
// 		void	update();
// 		void	print();
// 		void	clear();
// 		vec2i	getPos() const;
// };
// 
// #endif
