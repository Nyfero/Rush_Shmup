#ifndef SPACE_HPP
# define SPACE_HPP

# include "Game.hpp"
# include "Star.hpp"
# include <vector>


template <typename T>
class Space
{
	private:
		std::vector<T>	lst;
		Game			*game;

	public:
		//Constructors
		Space(Game * gameptr) : lst() { game = gameptr; };
		~Space() {};
		
		//Functions
		void	update() {
			for (size_t i = 0; i < lst.size(); i++) {
				if (lst.at(i).getPos().x > game->getWidth() || lst.at(i).getPos().x < 0 )
					lst.erase(lst.begin() + i);
				lst.at(i).update();
			}
		};

		void	create() {
			T entity(game);
			lst.push_back(entity);
		};
		
		std::vector<T> getData() const { return lst; };
};

#endif
