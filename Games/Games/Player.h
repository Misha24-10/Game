#pragma once
#include <SFML/Graphics.hpp>
const int MAXHP = 3;
const float MOVMENTSPEED = 10.f;
class Player
{
public:
	Player(float x = 0.f, float y = 0.f);
	~Player();

	void update(const sf::RenderTarget *target);
	void render(sf::RenderTarget* target);
	virtual void updateInput();
	const sf::RectangleShape &getShape() const;
	void updateWindowBoundCollision(const sf::RenderTarget* target);

	const int& getHp() const;
	const int& getHpMax() const;

	void takeDamage(const int damage);
	void gainHealth(const int health);
	sf::Vector2f getShape_() { return this->shape.getSize(); };
	void shapeIncrease();

	float getMovementSpeed() { return this->movementSpeed; };

protected:
	sf::RectangleShape shape;
	void initVariables();
	void initShape();
private:
	float movementSpeed;
	int hp;
	int hpMax;

};

