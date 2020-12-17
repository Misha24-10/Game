#include "Game.h"
#include <iostream>

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->sfmlEv))
	{
		switch (this->sfmlEv.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEv.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		}
	}

}

void Game::update()
{
	this->pollEvent();
	if (this->endGame == false)
	{
		this->spawmBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}

}

void Game::render()
{
	this->window->clear();

	this->player1.render(this->window);
	this->player2.render(this->window);

	for (auto i : this->balls) {
		i.render(*this->window);
	}
	this->renderGui(this->window);

	if (this->endGame) {
		this->window->draw(this->endGameText);
	}
	this->window->display();
}

void Game::spawmBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1;
	else
	{
		if (this->balls.size() < this->maxBalls)
			this->balls.push_back(Ball(*this->window, this->randomizeType()));
		this->spawnTimer = 0.f;

	}
}

const int Game::randomizeType()
{
	int type = BallsType::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 84 && randValue <= 90)
		type = BallsType::HEALING;
	else if (randValue > 90 && randValue <= 100)
		type = BallsType::DAMAGING;

	return type;
}

void Game::updateCollision()
{
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player1.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallsType::DEFAULT:
				this->pointsPlayer1++;
				this->player1.shapeIncrease();
				break;
			case BallsType::HEALING:
				this->player1.gainHealth(2);
				break;
			case BallsType::DAMAGING:
				this->player1.takeDamage(1);
				break;
			}
			this->balls.erase(this->balls.begin() + i);
		}
		else if (this->player2.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallsType::DEFAULT:
				this->pointsPlayer2++;
				this->player2.shapeIncrease();
				break;
			case BallsType::HEALING:
				this->player2.gainHealth(1);
				break;
			case BallsType::DAMAGING:
				this->player2.takeDamage(1);
				break;
			}
			this->balls.erase(this->balls.begin() + i);
		}
	}
}

void Game::renderGui(sf::RenderTarget *target)
{
	target->draw(this->guiTextPl1);
	target->draw(this->guiTextPl2);
}

void Game::updateGui()
{
	std::stringstream ss1, ss2;

	ss1 << "Player1\nPoints: " << this->pointsPlayer1 << "\n"
		<< "Health:" << this->player1.getHp() << "\\" << MAXHP << "\n";
	this->guiTextPl1.setString(ss1.str());

	ss2 << "Player2\nPoints: " << this->pointsPlayer2 << "\n"
		<< "Health:" << this->player2.getHp() << "\\" << MAXHP << "\n";
	this->guiTextPl2.setString(ss2.str());
}

void Game::updatePlayer()
{
	this->player1.update(this->window);

	this->player2.update(this->window);

	if (this->player1.getHp() <= 0 || this->player2.getHp() <= 0) {
		this->endGame = true;
		{
			winer();
			this->endGame = true;
		}
	}
	if (this->pointsPlayer1 >= 300 || this->pointsPlayer2 >= 300)
	{
		winer();
		this->endGame = true;
	}
}

void Game::winer()
{
	if (this->player1.getHp() <= 0 || this->pointsPlayer2 >= 150)
		this->endGameText.setString("   GAME OVER\nSecond Player won");
	else if (this->player2.getHp() <= 0 || this->pointsPlayer1 >= 150)
		this->endGameText.setString("   GAME OVER\nFirst Player won");

}

const bool & Game::getEndGame() const
{
	return this->endGame;
}

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = SPAWNTIMERMAX;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = MAXBALLS;
	this->pointsPlayer1 = 0;
	this->pointsPlayer1 = 0;


}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(1020, 800);
	this->window = new sf::RenderWindow(videoMode, "Agar.io_2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Dosis-Light.ttf"))
	{
		std::cout << "Error::Game::loadfile\n";
	}

}

void Game::initText()
{
	this->guiTextPl1.setFont(this->font);
	this->guiTextPl1.setFillColor(sf::Color::White);
	this->guiTextPl1.setCharacterSize(30);
	this->guiTextPl1.setString("");

	this->guiTextPl2.setFont(this->font);
	this->guiTextPl2.setFillColor(sf::Color::White);
	this->guiTextPl2.setCharacterSize(30);
	this->guiTextPl2.setString("");
	this->guiTextPl2.setPosition(880, 0);

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(320, 300));
	this->endGameText.setString("GAME OVER");
}
