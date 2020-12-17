#pragma once
#include <SFML/Graphics.hpp>

enum BallsType { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };
class Ball
{
public:
	Ball(const sf::RenderWindow &window, int type);
	~Ball();

	void update();
	void render(sf::RenderTarget &target);
	const sf::CircleShape getShape() const;


	const int & getType() const;
private:
	sf::CircleShape shape;
	int type;
	void initShape(const sf::RenderWindow &window);
};

