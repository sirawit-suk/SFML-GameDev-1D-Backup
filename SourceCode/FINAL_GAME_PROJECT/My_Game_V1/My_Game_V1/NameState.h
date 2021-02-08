#pragma once
#include "State.h"
#include "GameState.h"

class NameState :
	public State
{
public:

	//Constructor/Destructor
	NameState(RenderWindow* window, stack<State*>* states);
	virtual ~NameState();

	//Functions
	void UpdateSFMLEvent(const float& deltaTime, Event evnt);
	void UpdateInput(const float& deltaTime) {};
	void UpdateButtons();
	void Update(const float& deltaTime, Event evnt);
	void UpdateName();

	void Render(RenderTarget* target = nullptr);

private:

	Music battlesound;
	Music backgroundsound;

	int i;

	Text please;


	Text playername;
	char lastchar = ' ';
	string input = "";

	bool isReady;

	int mode;

	View view;

	Text instructText;
	
	bool isBlink;

	RectangleShape box;
	RectangleShape cursor;

	//Variables
	RectangleShape background;
	Texture bg;

};

