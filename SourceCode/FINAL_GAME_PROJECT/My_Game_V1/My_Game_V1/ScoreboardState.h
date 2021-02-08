#pragma once
#include "State.h"

class ScoreboardState : public State
{
public:

	//Constructor/Destructor
	ScoreboardState(RenderWindow* window, stack<State*>* states);
	virtual ~ScoreboardState();
	
	//Functions
	void UpdateInput(const float& deltaTime) {};
	void UpdateButtons();
	void Update(const float& deltaTime, Event evnt);

	void Render(RenderTarget* target = nullptr);

private:

	bool isHover;

	//Variables
	View view;

	vector <Button> buttons;

	RectangleShape box;

	RectangleShape background;
	Texture bg;

	Text NAME;
	Text KILL;
	Text SCORE;
};

