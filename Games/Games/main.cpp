#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "SecondPlayer.h"
#include "Game.h"
int main()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;

	while (game.running())
	{
		game.update();
		game.render();
	}
	return 0;
}

