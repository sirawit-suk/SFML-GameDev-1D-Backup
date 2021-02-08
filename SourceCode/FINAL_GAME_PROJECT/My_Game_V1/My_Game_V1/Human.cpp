#include "Human.h"

Human::Human()
{
	sf_walk.loadFromFile("Resource/Sound/walk.wav");
	soundeffect_walk.setBuffer(sf_walk);
	sf_shoot.loadFromFile("Resource/Sound/shoot_rifle.wav");
	soundeffect_shoot.setBuffer(sf_shoot);

	font.loadFromFile("Resource/Font/futura medium bt.ttf");

	//Random times
	srand(time(NULL));
	random = 0;
	randomdead = 0;

	//Times
	this->counterRandom = 0;
	this->counterBlink = 0;
	this->counterDead = 0.5;
	this->switchTime = 0.1;
	this->switchTimeDead = 0.6;
	this->totalTime = 0;

	this->transparentDead = 255;

	//Animations 
	row = 0;
	speed = 350; //standard
	faceRight = true;

	//Checkstate
	this->isAlive = true; //for live or die
	this->isDamage = false; //for receive damage
	this->isShot = false;  //for mouse click
	this->isPush = false; //for fire bullet

	//PlayerComponent //default
	hp = 80; 
	armor = 0.f;
	bulletRate = 50;
	bulletCount = 0;

	//Deletes
	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;

	this->gotoPosition.x = 0;
	this->gotoPosition.y = 0;

}

Human::~Human()
{
}

void Human::UpdateChangeColor(const float& deltaTime)
{

	if (counterBlink >= 0.3) {
		body.setFillColor(Color(255, 255, 255, 255));
		counterBlink = 0;
		isDamage = false;
	}
	else if (counterBlink >= 0.2) {
		body.setFillColor(Color(255, 95, 95, 255));
	}
	else if (counterBlink >= 0.1) {
		body.setFillColor(Color(255, 255, 255, 255));
	}
	else if (counterBlink >= 0) {
		body.setFillColor(Color(255, 95, 95, 255));
	}
	counterBlink += deltaTime;

}

void Human::UpdateChangeColorDead(const float& deltaTime)
{
	body.setFillColor(Color(255, 255, 255, transparentDead));
	if (transparentDead > 0) {
		transparentDead -= deltaTime * 70;
	}
}

void Human::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}