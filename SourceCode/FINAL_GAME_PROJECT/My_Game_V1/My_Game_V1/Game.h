#pragma once
#include "MainMenuState.h"



class Game
{
public:

	//Constructor/Destructor
	Game();
	virtual ~Game();

	//Functions

	//Update
	void SFML_Events();
	void UpdateDt() { deltaTime = clock.restart().asSeconds(); };
	void Update();

	//Core
	void Run();

	//Render
	void Render();

private:

	RenderWindow* window;

	stack<State*> states;

	//Clock deltaTime
	Clock clock;
	float deltaTime = 0.f;

	Event evnt;

	Texture mousecursorTexture;
	RectangleShape mousecursor;

	Vector2f mousePosView;
};

