#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Fade
{

public:
	//Constructors/Destructors
	Fade(RenderWindow& window);
	~Fade();

	//Functions
	void Update(const float& deltaTime);
	void Draw(RenderTarget& target); //RenderWindow& window

	bool isFade;
	bool isFadeDone;

	bool isBright;
	bool isBrightDone;

	float setValue;

private:

	//Variables


	RectangleShape fade;
	float fadeValue;
	float a;


};

