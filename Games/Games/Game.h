#pragma once

#include <ctime>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#include "Ball.h"
#include "SecondPlayer.h"

const int MAXBALLS = 15;
const float SPAWNTIMERMAX = 8.f;

class Game
{
public:
	Game();
	~Game();
	const bool running() const;
	void update();
	void render();

	const bool& getEndGame() const;
private:

	const int randomizeType();
	void pollEvent();
	void updateCollision();
	void renderGui(sf::RenderTarget *target);
	void updateGui();
	void updatePlayer();
	void winer();
	void spawmBalls();

	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	bool endGame;
	sf::Event sfmlEv;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

	int pointsPlayer1;
	int pointsPlayer2;

	sf::Font font;
	sf::Text guiTextPl1;
	sf::Text guiTextPl2;
	sf::Text endGameText;

	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;
	Player player1;
	SecondPlayer player2;
	std::vector<Ball> balls;
};

