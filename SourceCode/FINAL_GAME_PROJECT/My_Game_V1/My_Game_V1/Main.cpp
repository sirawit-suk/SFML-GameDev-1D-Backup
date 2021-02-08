#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
	Game game;
	game.Run();

	return 0;
}
