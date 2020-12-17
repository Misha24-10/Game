#include "SecondPlayer.h"
void SecondPlayer::updateInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->shape.move(-this->getMovementSpeed(), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->shape.move(this->getMovementSpeed(), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->shape.move(0.f, -this->getMovementSpeed());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->shape.move(0.f, this->getMovementSpeed());
	}
}

void SecondPlayer::initShape()
{
	this->shape.setFillColor(sf::Color::White);
	this->shape.setSize(sf::Vector2f(20.f, 20.f));
	this->shape.setPosition(700, 500);

}