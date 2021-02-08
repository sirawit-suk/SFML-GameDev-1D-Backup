#include "Item.h"

Item::Item(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition, int mode)
	:animation(texture, imageCount)
{
	this->mode = mode;		//First aid = 0, gun = 1
	this->speed = speed;
	this->switchTime = switchTime;
	this->switchTimeAnimation = 1.2;
	this->switchTimeDead = 5;

	this->dtanimation = 0;

	this->row = 0;
	this->isCollect = false;
	this->isStop = false;

	this->totalTime = 0;
	this->totalTimeAnimation = 0;
	this->totalTimeDelete = 0;
	this->randomstop = 0;

	this->transparentDead = 255;

	body.setSize(Vector2f(60.f * 6, 60.f * 3));
	body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
	body.setPosition(setPosition);
	body.setTexture(texture);

	hitbox.setSize(Vector2f(50.f, 50.f));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(body.getPosition().x, body.getPosition().y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Green);
	hitbox.setOutlineThickness(1.f);

	this->OutscreenPosition.x = 1000;
	this->OutscreenPosition.y = 5000;

	if (mode == 2) {
		body.setSize(Vector2f(80.f * 3, 80.f * 3));
		body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
		body.setPosition(setPosition);
		body.setTexture(texture);

		hitbox.setSize(Vector2f(70.f, 60.f));
		hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		hitbox.setPosition(body.getPosition().x, body.getPosition().y);
		hitbox.setFillColor(Color::Transparent);
		hitbox.setOutlineColor(Color::Green);
		hitbox.setOutlineThickness(1.f);
	}
	if (mode == 3) {
		body.setSize(Vector2f(80.f*2, 80.f*2));
		body.setOrigin((body.getSize().x / 2.f), (body.getSize().y / 2.f));
		body.setPosition(setPosition);
		body.setTexture(texture);

		hitbox.setSize(Vector2f(70.f, 60.f));
		hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		hitbox.setPosition(body.getPosition().x, body.getPosition().y);
		hitbox.setFillColor(Color::Transparent);
		hitbox.setOutlineColor(Color::Green);
		hitbox.setOutlineThickness(1.f);
	}
}

Item::~Item()
{
}

void Item::Update(const float& deltaTime)
{
	if (mode != 2 && mode != 3) {
		totalTime += deltaTime;
		if (totalTime >= 0.5 && isStop == false) {
			randomstop = (rand() % 200) + 810;
			totalTime = 0;
		}

		if (hitbox.getPosition().y < 600) {
			row = 0;
			velocity.y = speed;
			animation.Update(row, deltaTime, true, switchTime);
		}
		else if (hitbox.getPosition().y >= 600) {
			row = 0;
			velocity.y = speed;
			if (hitbox.getPosition().y > randomstop) {

				isStop = true;
				totalTimeAnimation += deltaTime;
				if (totalTimeAnimation < switchTimeAnimation) {
					row = 1;
				}
				else {
					row = 2;
				}
				velocity.y = 0;
			}
		}

		if (isCollect == true) {
			if (mode == 0) {		//FirstAids
				row = 3;
				body.setFillColor(Color(200, 200, 200, 255));
				totalTimeDelete += deltaTime;
				if (totalTimeDelete >= switchTimeDead) {
					UpdateChangeColorDead(deltaTime);
				}
				if (totalTimeDelete >= switchTimeDead * 1.7) {
					SetDeletePosition();
				}
			}
			else if (mode == 1) {	//Gun
				SetDeletePosition();
			}
		}
		animation.Update(row, deltaTime, true, switchTime);
		body.setTextureRect(animation.xyRect);

		hitbox.move(velocity * deltaTime);
		body.setPosition(hitbox.getPosition().x - 90, hitbox.getPosition().y - 65);
	}
	
	if (mode == 2) {
		if (isCollect == true) {
			SetDeletePosition();
		}
		animation.Update(0, deltaTime, true, switchTime);
		body.setTextureRect(animation.xyRect);

		hitbox.move(velocity * deltaTime);
		body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 80);
	}
	if (mode == 3) {
		if (isCollect == true) {
			SetDeletePosition();
		}
		animation.Update(0, deltaTime, true, switchTime);
		body.setTextureRect(animation.xyRect);

		hitbox.move(velocity * deltaTime);
		body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
	}

}

void Item::UpdateChangeColorDead(const float& deltaTime)
{
	body.setFillColor(Color(255, 255, 255, transparentDead));
	if (transparentDead > 0) {
		transparentDead -= deltaTime * 70;
	}
}

void Item::SetDeletePosition()
{
	hitbox.setPosition(OutscreenPosition);
}

void Item::Draw(RenderTarget& target)
{
	target.draw(body);
	//target.draw(hitbox);
	
}
