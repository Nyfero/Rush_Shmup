#ifndef STAR_HPP
# define STAR_HPP

# include "IEntity.hpp"
# include "Game.hpp" 

class Star: public IEntity
{
	private:
		vec2i	pos;
		float	velocity;

	public:
		Star(Game const &game);
		~Star();
		void	update();
		vec2i	getPos() const;
};

#endif
