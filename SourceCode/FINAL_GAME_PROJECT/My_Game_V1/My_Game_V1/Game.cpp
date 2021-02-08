#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(1920, 1080), "World War I: ROAD TO CAMBRAI", Style::Fullscreen); //,Style::Fullscreen
	window->setFramerateLimit(120);
	window->setVerticalSyncEnabled(false);

	this->states.push(new MainMenuState(window, &states));
	//this->states.push(new GameState(window, &states));
	//this->states.push(new GameState2(window, &states));
	//this->states.push(new LoadingState2(window, &states));

	mousecursorTexture.loadFromFile("Resource/Component/mousecursor.png");
	mousecursorTexture.setSmooth(true);
	mousecursor.setTexture(&mousecursorTexture);
	mousecursor.setSize(Vector2f(30,30));

	window->setMouseCursorVisible(false);
}

Game::~Game()
{
	delete window;
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void Game::SFML_Events()
{
	while (window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::Resized:
			//Resize_View(window);
			break;
		}
	}
}

void Game::Update()
{
	mousePosView = window->mapPixelToCoords(Mouse::getPosition(*window));
	mousecursor.setPosition(Vector2f(mousePosView));

	UpdateDt();
	if (!states.empty())
	{
		//Update states loop
		states.top()->Update(deltaTime,evnt);

		//Check if it Quit or not? 
		if (states.top()->getQuit())
		{			
			delete states.top();
			states.pop();	//Form MainMenu and GameState

		}
	}
	else
	{
		//Good bye 
		this->window->close();
	}
}

void Game::Render()
{
	window->clear();
	if (!this->states.empty())
		this->states.top()->Render();
	window->draw(mousecursor);
	window->display();
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		SFML_Events();

		Update();

		Render();
	}
}
