#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Animation
{
public:

	//Constructor/Destructor
	Animation(Texture* texture,Vector2u imageCount);
	~Animation();

	//Function
	void Update(int row, float deltaTime, bool faceRight, float switchTime);
	bool isAnimationDone() { return isDone; }
	bool isAnimationDoneTank() { return isDonetank; }

	//Variable
	IntRect xyRect;

	bool isDone;
	bool isDonetank;

private:

	int rowTemp;

	//Variable
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
};

