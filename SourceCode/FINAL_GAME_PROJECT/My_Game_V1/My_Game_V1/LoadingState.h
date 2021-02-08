#pragma once
#include "State.h"
#include "GameState2.h"

class LoadingState :
	public State
{
public:

	//Constructor/Destructor
	LoadingState(RenderWindow* window, stack<State*>* states);
	virtual ~LoadingState();

	//Functions
	void UpdateInput(const float& deltaTime) {};
	void UpdateButtons();
	void Update(const float& deltaTime, Event evnt);

	void Render(RenderTarget* target = nullptr);

private:

	View view;

	bool isReady = false;

	Text loadingText;

	Text instructText;

	//Variables
	RectangleShape background;
	Texture bg;

};

