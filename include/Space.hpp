#ifndef SPACE_HPP
# define SPACE_HPP

# include "IEntity.hpp"
# include "Game.hpp"
# include "Bullet.hpp"
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
		Space(Game * gameptr) : lst(), game(gameptr) { }
		~Space() {};
		
		//Functions
		void	update() {
			for (size_t i = 0; i < lst.size(); i++) {
				if (lst.at(i).getPos().x > game->getWidth() || lst.at(i).getPos().x < 0 )
					lst.erase(lst.begin() + i);
				else
					lst.at(i).update();
			}
		};
		
		void	create() {
			T entity(game);
			lst.push_back(entity);
		};
		
		std::vector<T> getData() const { return lst; };
};

template <>
class Space<Bullet>
{
	private:
		std::vector<Bullet>	lst;
		Game			*game;

	public:
		//Constructors
		Space(Game * gameptr) : lst(), game(gameptr) { }
		~Space() {};
		
		//Functions
		void	update() {
			for (size_t i = 0; i < lst.size(); i++) {
				if (lst.at(i).getPos().x > game->getWidth() || lst.at(i).getPos().x < 0 )
					lst.erase(lst.begin() + i);
				else
					lst.at(i).update();
			}
		};

		void	create(Source source, float velocity, int_fast16_t x, int_fast16_t y) {
			Bullet entity(game, source, velocity, x, y);
			lst.push_back(entity);
		};
		
		std::vector<Bullet> getData() const { return lst; };
};

#endif
