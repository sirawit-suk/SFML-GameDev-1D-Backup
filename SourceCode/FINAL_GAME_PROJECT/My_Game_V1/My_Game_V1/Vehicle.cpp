#include "Vehicle.h"

Vehicle::Vehicle()
{

	//Random times
	srand(time(NULL));
	random = 0;
	randomdead = 0;

	isFire = false;

	//Times
	this->counterRandom = 0;
	this->counterBlink = 0;
	this->counterDead = 0.5;
	this->switchTime = 0.1;
	this->switchTimeDead = 0.6;

	this->totalTime = 0.f;

	this->transparentDead = 255;

	//Animations 
	row = 0;
	speed = 350; //standard
	faceRight = true;

	this->mode = 0;

	//Checkstate
	this->isAlive = true; //for live or die
	this->isDamage = false; //for receive damage
	this->isShot = false;  //for mouse click
	this->isPush = false; //for fire bullet

	//VehicleComponent //default
	hp = 500;
	bulletRate = 20;
	bulletCount = 0;

	//Deletes
	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;

	this->gotoPosition.x = 0;
	this->gotoPosition.y = 0;

	this->velocity.x = 0;
	this->velocity.y = 0;

	this->setPositionTemp.x = 0;
	this->setPositionTemp.y = 0;
}

Vehicle::~Vehicle()
{
}

void Vehicle::UpdateChangeColor(const float& deltaTime)
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

void Vehicle::UpdateChangeColorDead(const float& deltaTime)
{
	body.setFillColor(Color(255, 255, 255, transparentDead));
	if (transparentDead > 0) {
		transparentDead -= deltaTime * 70;
	}
}

void Vehicle::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}

void Vehicle::SetPosition(int x, int y)
{
	hitbox.setPosition(x, y);
}

void Vehicle::SetPosition5800()
{
	hitbox.setPosition(5800,600);
}

void Vehicle::SetPosition9000()
{
	hitbox.setPosition(9000, 600);
}
