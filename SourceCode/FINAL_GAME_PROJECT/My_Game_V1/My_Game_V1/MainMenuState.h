#pragma once
#include "State.h"
#include "GameState.h"
#include "ScoreboardState.h"
#include "NameState.h"
#include "LoadingState.h"
#include "GameState2.h"

class MainMenuState : public State
{
public:

	//Constructor/Destructor
	MainMenuState(RenderWindow* window, stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void UpdateInput(const float& deltaTime) {};
	void UpdateButtons(const float& deltaTime);
	void Update(const float& deltaTime, Event evnt);
	void Render(RenderTarget* target = nullptr);

private:

	bool isHover0;
	bool isHover1;
	bool isHover2;

	int mode;
	//Variables
	vector <Button> buttons;
	View view;

	//Variables
	RectangleShape background;
	Texture bg;

	Music background_Sound;


	Text title;
	Text myname;
	Text mynumber;
	Text myDegree;

	Text version;
	Text date;
};

