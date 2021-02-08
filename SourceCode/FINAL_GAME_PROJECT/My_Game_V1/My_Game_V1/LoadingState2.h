#pragma once
#include "State.h"
#include "ScoreboardState.h"

class LoadingState2 :
	public State
{
public:

	//Constructor/Destructor
	LoadingState2(RenderWindow* window, stack<State*>* states);
	virtual ~LoadingState2();

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

