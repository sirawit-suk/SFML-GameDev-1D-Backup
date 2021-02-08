#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

using namespace sf;
using namespace std;

class Button
{
public:
	Button(float x, float y, float width, float height,
		Font* font, string text,
		Color idleColor, Color hoverColor, Color ActiveColor);
	~Button();

	//Accessors
	const bool isHovered() const;
	const bool isPressed() const;
	//Funcitons
	void Update(const Vector2f mousePos);
	void Draw(RenderTarget& target);

private:


	SoundBuffer type;
	Sound typesound;

	short unsigned buttonState;

	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

};

