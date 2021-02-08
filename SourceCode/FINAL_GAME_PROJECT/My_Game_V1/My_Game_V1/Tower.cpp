#include "Tower.h"

Tower::Tower(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount2, Vector2u imageCount3, float switchTime, Vector2f setPosition, int mode)
	:animationbomb(bombtexture, imageCount2), animationfire(firetexture, imageCount3)
{

	this->mode = mode;
	this->switchTime = switchTime;
	this->row = 0;
	this->faceRight = true;

	this->isAlive = true;
	this->isDamage = false;
	this->counterBlink = 0.f;

	this->isAlreadyBoom = false;
	this->isStart = false;

	body.setSize(Vector2f(200.f * 2, 200.f * 2));
	body.setOrigin(body.getSize().x / 2.f, body.getSize().y / 2.f);
	body.setPosition(setPosition);
	body.setTexture(texture);

	hp = 500;

	hpbar.setFillColor(Color(0, 255, 0, 240));
	hpbar.setSize(Vector2f(hp, 12));

	hpbarbox.setSize(Vector2f(hp, 12));
	hpbarbox.setFillColor(Color(0, 0, 0, 150));
	hpbarbox.setOutlineColor(Color(0, 0, 0, 150));
	hpbarbox.setOutlineThickness(2);


	hitbox.setSize(Vector2f(180, 140.f));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(body.getPosition().x, body.getPosition().y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(1.f);

	bombeffect.setSize(Vector2f(90 * 4, 90 * 4));
	bombeffect.setOrigin(bombeffect.getSize().x / 2.f, bombeffect.getSize().y / 2.f);
	bombeffect.setPosition(setPosition);
	bombeffect.setTexture(bombtexture);

	fireeffect1.setSize(Vector2f(90 * 4, 90 * 4));
	fireeffect1.setOrigin(fireeffect1.getSize().x / 2.f, fireeffect1.getSize().y / 2.f);
	fireeffect1.setFillColor(Color(255, 255, 255, 240));
	fireeffect1.setPosition(setPosition);
	fireeffect1.setTexture(firetexture);

	fireeffect2.setSize(Vector2f(90 * 2, 90 * 2));
	fireeffect2.setOrigin(fireeffect2.getSize().x / 2.f, fireeffect2.getSize().y / 2.f);
	fireeffect2.setFillColor(Color(255, 255, 255, 230));
	fireeffect2.setPosition(setPosition);
	fireeffect2.setTexture(firetexture);

}

Tower::~Tower()
{
}

void Tower::Update(const float& deltaTime)
{
	hpbar.setSize(Vector2f(hp, 12));
	hpbarbox.setSize(Vector2f(500, 12));

	/////////////////////////////////////////////// Animation //////////////////////////////////////////////////

	//Animations
	row = 0;

	hpbar.setPosition(hitbox.getPosition().x - 240, hitbox.getPosition().y - 120);
	hpbarbox.setPosition(hitbox.getPosition().x - 240, hitbox.getPosition().y - 120);
	body.setPosition(hitbox.getPosition().x-20, hitbox.getPosition().y-25);

	//
	if (isAlive == false)
	{
		animationbomb.Update(0, deltaTime, faceRight, switchTime);
		bombeffect.setTextureRect(animationbomb.xyRect);
		bombeffect.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);

		animationfire.Update(0, deltaTime, faceRight, 0.3);
		fireeffect1.setTextureRect(animationfire.xyRect);
		fireeffect1.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);

		animationfire.Update(0, deltaTime, faceRight, 0.2);
		fireeffect2.setTextureRect(animationfire.xyRect);
		fireeffect2.setPosition(hitbox.getPosition().x - 160, hitbox.getPosition().y + 50);
	}

	if (isDamage == true)
	{
		UpdateChangeColor(deltaTime);
	}
}

void Tower::UpdateChangeColor(const float& deltaTime)
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

void Tower::Draw(RenderTarget& target)
{
	if (isAlive == true && isStart == true && mode ==1)
	{
		target.draw(hpbarbox);
		target.draw(hpbar);
	}

	target.draw(body);
	//target.draw(hitbox);

	if (isAlive == false)
	{
		target.draw(fireeffect1);
		target.draw(fireeffect2);
		if (animationbomb.isAnimationDoneTank() == false) {
			target.draw(bombeffect);
		}
	}
}
