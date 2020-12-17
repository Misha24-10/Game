#include "Player.h"

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

void Player::update(const sf::RenderTarget *target)
{

	this->updateInput();
	this->updateWindowBoundCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Player::updateWindowBoundCollision(const sf::RenderTarget * target)
{
	// left 
	sf::FloatRect playerBound = this->shape.getGlobalBounds();
	if (playerBound.left <= 0.f)
		this->shape.setPosition(0.f, playerBound.top);
	// right
	else if (playerBound.left + playerBound.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBound.width, playerBound.top);
	//top
	if (playerBound.top <= 0.f)
		this->shape.setPosition(playerBound.left, 0.f);
	//bottom
	else if (playerBound.top + playerBound.height >= target->getSize().y)
		this->shape.setPosition(playerBound.left, target->getSize().y - playerBound.height);
	// left top
	if (playerBound.left <= 0.f && playerBound.top <= 0.f)
		this->shape.setPosition(0.f, 0.f);
	// right top
	if (playerBound.left + playerBound.width >= target->getSize().x && playerBound.top <= 0.f)
		this->shape.setPosition(target->getSize().x - playerBound.width, 0.f);
	// left bottom
	if (playerBound.left <= 0.f && playerBound.top + playerBound.height >= target->getSize().y)
		this->shape.setPosition(0.f, target->getSize().y - playerBound.height);
	// right bottom
	if (playerBound.left + playerBound.width >= target->getSize().x && playerBound.top + playerBound.height >= target->getSize().y)
		this->shape.setPosition(target->getSize().x - playerBound.width, target->getSize().y - playerBound.height);
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}
	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
	{
		this->hp += health;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void Player::shapeIncrease()
{
	if (this->getShape_().x < 300 || this->getShape_().y < 300) {
		sf::Vector2f shape_ = this->getShape_();
		shape_.x = shape_.x + 1;
		shape_.y = shape_.y + 1;
		this->shape.setSize(shape_);
	}
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

const sf::RectangleShape & Player::getShape() const
{
	return this->shape;
}


void Player::initVariables()
{
	this->movementSpeed = MOVMENTSPEED;
	this->hpMax = MAXHP;
	this->hp = this->hpMax;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setSize(sf::Vector2f(20.f, 20.f));
	this->shape.setPosition(200, 500);

}
