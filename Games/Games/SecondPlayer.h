#pragma once
#include "Player.h"
class SecondPlayer : public Player
{
public:
	SecondPlayer(float x = 0.f, float y = 0.f)
	{
		this->shape.setPosition(x, y);
		this->initVariables();
		this->initShape();
	}
private:
	virtual void updateInput();
	void initShape();
};

