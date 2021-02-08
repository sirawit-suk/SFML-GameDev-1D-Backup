#include "Bomb.h"

Bomb::Bomb(Texture* texture, Vector2u imageCount, float switchTime, float speed, bool faceRight, Vector2f setPosition, int mode)
	:animation(texture, imageCount)
{
	this->mode = mode;		//Bomb =0, Blood = 1
	this->speed = speed;
	this->switchTime = switchTime;
	this->faceRight = faceRight;

	this->totalTime = 0;
	this->totalDeadTime = 0;
	this->row = 0;
	this->isBoom = false;
	this->isHit = false;

	this->isAlreadyBoom = false;

	body.setSize(Vector2f(400, 400));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setTexture(texture);

	hitbox.setSize(Vector2f(80, 90));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(setPosition.x,setPosition.y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(1.f);

	areabox.setSize(Vector2f(body.getSize().x / 2, body.getSize().y / 2));
	areabox.setOrigin((areabox.getSize().x / 2.f), (areabox.getSize().y / 2.f));
	areabox.setPosition(setPosition);
	areabox.setFillColor(Color::Transparent);
	areabox.setOutlineColor(Color::Red);
	areabox.setOutlineThickness(1.f);

	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;

	this->transparentDead = 255;
}

Bomb::~Bomb()
{
}

void Bomb::Update(const float& deltaTime)
{
	if (isAlreadyBoom == true) {
		isBoom = false;
	}

	if (isHit == false) {
		row = 0;
	}
	else if (isHit == true) {
		totalTime += deltaTime*2;
		row = 1;
		if (totalTime > 5 && isAlreadyBoom == false) {
			isBoom = true;
		}
	}
	if (isBoom == true) {
		isAlreadyBoom = true;
	}

	if (isAlreadyBoom == true) {
		row = 2;
	}

	if (animation.isAnimationDone() == true) {
		totalDeadTime += deltaTime;
		UpdateChangeColorDead(deltaTime);
		row = 3;
	}
	if (totalDeadTime > 5 ) {
		SetDeletePosition();
		totalTime = 0;
	}
	animation.Update(row, deltaTime, faceRight, switchTime);
	body.setTextureRect(animation.xyRect);
	body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 80);
}

void Bomb::UpdateChangeColorDead(const float& deltaTime)
{
	body.setFillColor(Color(255, 255, 255, transparentDead));
	if (transparentDead > 0) {
		transparentDead -= deltaTime * 40;
	}
}

void Bomb::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}

void Bomb::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);
	//target.draw(areabox);
}
