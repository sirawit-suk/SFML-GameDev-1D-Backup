#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>
#include <sstream>
#include "Animation.h"
#include "Button.h"

using namespace sf;
using namespace std;


class PauseMenu
{
public:

	//Constructor/Destructor
	PauseMenu(RenderWindow& window, Font& font, View& view);
	~PauseMenu();

	//Functions
	const bool& isButtonPressed(int i) { return buttons[i].isPressed(); };
	const bool& isButtonHovered(int i) { return buttons[i].isHovered(); };

	void addButton(float x, float y, const string text);
	void initialPause(RenderWindow& window, View& view);
	void Update(Vector2f& mousePosView);
	void Draw(RenderTarget& target);

private:

	//Variables
	RectangleShape background;
	RectangleShape windowbox;

	vector <Button> buttons;

	Font& font;
	Text menuText;
	Text areyousureText;

};

