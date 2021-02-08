#include "Effect.h"

Effect::Effect(Texture* texture, Vector2u imageCount, float switchTime, float speed, bool faceRight, Vector2f setPosition, int mode)
	:animation(texture, imageCount)
{
	this->mode = mode;		//Bomb =0, Blood = 1
	this->speed = speed;
	this->switchTime = switchTime;
	this->faceRight = faceRight;

	this->totalTime = 0;
	this->row = 0;
	this->isBomb = false;
	this->isStop = false;
	totalTimeAnimation = 0;

	body.setSize(Vector2f(60.f * 6, 60.f * 6));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setTexture(texture);

	hitbox.setSize(Vector2f(body.getSize().x/2, body.getSize().y/2));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(setPosition);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(1.f);

	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;

	this->transparentDead = 255;

	velocity.x = 0;
	velocity.y = 0;
}

Effect::~Effect()
{
}

void Effect::Update(const float& deltaTime)
{
	totalTime += deltaTime;
	if (isMissionbomb == false) {
		if (totalTime >= 0.5 && isStop == false) {
			randomstop = (rand() % 200) + 700;
			totalTime = 0;
		}
	}
	
	if(hitbox.getPosition().y < 700) {
		row = 0;
		velocity.y = speed;
	}
	else if (hitbox.getPosition().y >= 700) {
		velocity.y = speed;
		if (totalTimeAnimation != 0) {
			isBomb = false;
		}
		if (hitbox.getPosition().y > randomstop && isBomb == false && totalTimeAnimation == 0) {
			isStop = true;
			isBomb = true;
		}
		if (isStop == true) {
			totalTimeAnimation += deltaTime;
			row = 1;
			velocity.y = 0;
			velocity.y = 0;
		}
	}

	if (totalTimeAnimation >= 2 ) {
		SetDeletePosition();
		totalTimeAnimation = 0;
	}

	hitbox.move(velocity * deltaTime);
	animation.Update(row, deltaTime, faceRight, switchTime);
	body.setTextureRect(animation.xyRect);
	body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y-100);
}

void Effect::UpdateChangeColorDead(const float& deltaTime)
{
	body.setFillColor(Color(255, 255, 255, transparentDead));
	if (transparentDead > 0) {
		transparentDead -= deltaTime * 300;
	}
}

void Effect::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}

void Effect::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);
}
