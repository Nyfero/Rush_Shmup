#ifndef ENNEMIE_HPP
# define ENNEMIE_HPP

# include "IEntity.hpp"
# include "Game.hpp"

class Ennemie: public IEntity
{
	private:
		const char	disp;
		vec2i	pos;
		const bool	front = 1;
		vec2i	velocity;
		Ennemie() = 0;
	
	public:
		//Constructors
		Ennemie(char c, int x, int y);
		~Ennemie();
		
		//Functions
		void	update();
		void	print() const;
		void	clear();
}

#endif
