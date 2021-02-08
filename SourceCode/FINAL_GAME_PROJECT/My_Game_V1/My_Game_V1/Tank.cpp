#include "Tank.h"

Tank::Tank(Texture* texture, Texture* bombtexture, Texture* firetexture, Vector2u imageCount1, Vector2u imageCount2, Vector2u imageCount3,float switchTime, float speed, Vector2f setPosition, int mode)
	: animation(texture, imageCount1), animationbomb(bombtexture, imageCount2), animationfire(firetexture, imageCount3)
{
	//mode 0 = enemy
	//mode 1 = ally

	this->speed = speed;
	this->switchTime = switchTime;
	this->mode = mode;

	isRange = false;

	body.setSize(Vector2f(240*3, 240*3));
	body.setOrigin(body.getSize().x / 2.f, body.getSize().y / 2.f);
	body.setPosition(setPosition);
	body.setTexture(texture);
	
	if (mode == 1) {
		hpbar.setFillColor(Color(0, 255, 0, 240));
		hpbar.setSize(Vector2f(hp, 12));

		hpbarbox.setSize(Vector2f(hp, 12));
		hpbarbox.setFillColor(Color(0, 0, 0, 150));
		hpbarbox.setOutlineColor(Color(0, 0, 0, 150));
		hpbarbox.setOutlineThickness(2);


		hitbox.setSize(Vector2f(194.f * 2, 76.f * 2));
		hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		hitbox.setPosition(body.getPosition().x, body.getPosition().y);
		hitbox.setFillColor(Color::Transparent);
		hitbox.setOutlineColor(Color::Red);
		hitbox.setOutlineThickness(1.f);

		areabox2.setSize(Vector2f(194.f * 2.5, 76.f * 3));
		areabox2.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		areabox2.setPosition(body.getPosition().x + 200, body.getPosition().y - 45);
		areabox2.setFillColor(Color::Transparent);
		areabox2.setOutlineColor(Color::Red);
		areabox2.setOutlineThickness(1.f);

		areabox.setSize(Vector2f(194.f * 2.5, 76.f * 3));
		areabox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		areabox.setPosition(body.getPosition().x + 200, body.getPosition().y + 60);
		areabox.setFillColor(Color(255, 255, 0, 100));
		areabox.setOutlineColor(Color(255, 255, 0, 150));
		areabox.setOutlineThickness(1.f);
	}
	else if (mode == 0) {
		hp = 2000;

		hitbox.setSize(Vector2f(194.f * 2, 76.f * 2));
		hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
		hitbox.setPosition(body.getPosition().x, body.getPosition().y);
		hitbox.setFillColor(Color::Transparent);
		hitbox.setOutlineColor(Color::Red);
		hitbox.setOutlineThickness(1.f);

		hpbar.setFillColor(Color(255, 0, 0, 240));
		hpbar.setSize(Vector2f(hp, 30));

		hpbarbox.setSize(Vector2f(hp, 30));
		hpbarbox.setFillColor(Color(0, 0, 0, 150));
		hpbarbox.setOutlineColor(Color(0, 0, 0, 150));
		hpbarbox.setOutlineThickness(2);
	}

	bombeffect1.setSize(Vector2f(90 * 4, 90 * 4));
	bombeffect1.setOrigin(bombeffect1.getSize().x / 2.f, bombeffect1.getSize().y / 2.f);
	bombeffect1.setPosition(setPosition);
	bombeffect1.setTexture(bombtexture);

	fireeffect.setSize(Vector2f(90 * 4, 90 * 4));
	fireeffect.setOrigin(fireeffect.getSize().x / 2.f, fireeffect.getSize().y / 2.f);
	fireeffect.setFillColor(Color(255, 255, 255, 210));
	fireeffect.setPosition(setPosition);
	fireeffect.setTexture(firetexture);

	fireeffect2.setSize(Vector2f(90 * 2, 90 * 2));
	fireeffect2.setOrigin(fireeffect2.getSize().x / 2.f, fireeffect2.getSize().y / 2.f);
	fireeffect2.setFillColor(Color(255, 255, 255, 200));
	fireeffect2.setPosition(setPosition);
	fireeffect2.setTexture(firetexture);

	fireeffect3.setSize(Vector2f(90 * 3, 90 * 3));
	fireeffect3.setOrigin(fireeffect3.getSize().x / 2.f, fireeffect3.getSize().y / 2.f);
	fireeffect3.setFillColor(Color(255, 255, 255, 190));
	fireeffect3.setPosition(setPosition);
	fireeffect3.setTexture(firetexture);

	isAppearArea = false;
	changeFade = false;
	colorValue = 150;
}

Tank::~Tank()
{
}

void Tank::TankInput(const float& deltaTime, Vector2f gotoPosition)
{
	velocity.x = 0;
	velocity.y = 0;

	if (counterRandom >= 1.f)
	{
		random = rand() % 200;
		counterRandom = 0.f;
		this->gotoPosition = gotoPosition;
	}
	counterRandom += deltaTime;

	if (gotoPosition.x - hitbox.getPosition().x >= 300 && random >= 0 && random < 40) { //go Right
		velocity.x += speed;
	}
	if (gotoPosition.x - hitbox.getPosition().x < 300 && random >= 40 && random < 80) { //go Left
		velocity.x -= speed;
	}
	if (random >= 100 && random < 150) {}

	//Bullets
	if (bulletCount < bulletRate) { bulletCount++; isFire = false; }
	if (random >= 150 && random < 200 && bulletCount >= bulletRate && isFire == false)
	{
		isShot = true;
		isFire = true;
		bulletCount = 0;

	}
	else if (!(random >= 150 && random <= 200))
	{
		isShot = isFire;
		isPush = isFire;
	}

	if (isFire == true) {
		if (totalTime >= 0.5) {
			isPush = true;
			totalTime = 0;
		}
		else
		{
			isPush = false;
		}
		totalTime += deltaTime*10;
	}

}

void Tank::Update(const float& deltaTime)
{
	if (mode == 1) {	//Ours

		if (hp >= 500) {
			hp = 500;
		}

		hpbar.setSize(Vector2f(hp, 12));
		hpbarbox.setSize(Vector2f(500, 12));

	}
	else if (mode == 0){	//Enemy

		if (hp <= 0) {
			hp = 0;
			isAlive = false;
		}
	
		hpbar.setSize(Vector2f(hp/2.f, 30));
		hpbarbox.setSize(Vector2f(1000, 30));
	}
	/////////////////////////////////////////////// Animation //////////////////////////////////////////////////

	//Animations
	if (isAlive == true) {
		row = 0;
		if (isDamage == true) {
			UpdateChangeColor(deltaTime);
		}
		if (isPush == true) {
			row = 1;
		}

	}
	else {
		row = 2;
	}

	if (isRange == true) 
	{
		velocity.x = speed;
		isRange = false;
	}
	else
	{
		velocity.x = 0.f;
	}

	animation.Update(row, deltaTime, faceRight, switchTime);
	body.setTextureRect(animation.xyRect);

	if (mode == 1) {
		hpbar.setPosition(hitbox.getPosition().x - 240, hitbox.getPosition().y - 120);
		hpbarbox.setPosition(hitbox.getPosition().x - 240, hitbox.getPosition().y - 120);
	}
	else if (mode == 0) {
		hpbar.setPosition(460, 950);
		hpbarbox.setPosition(460, 950);
	}
	

	hitbox.move(velocity * deltaTime);
	body.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
	areabox2.setPosition(body.getPosition().x + 200, body.getPosition().y - 45);
	areabox.setPosition(body.getPosition().x + 200, body.getPosition().y + 60);

	//
	if (isAlive == false) 
	{
		animationbomb.Update(0, deltaTime, faceRight, switchTime);
		bombeffect1.setTextureRect(animationbomb.xyRect);
		bombeffect1.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);

		animationfire.Update(0, deltaTime, faceRight, 0.3);
		fireeffect.setTextureRect(animationfire.xyRect);
		fireeffect.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);

		animationfire.Update(0, deltaTime, faceRight, 0.2);
		fireeffect2.setTextureRect(animationfire.xyRect);
		fireeffect2.setPosition(hitbox.getPosition().x-160, hitbox.getPosition().y +50);

		animationfire.Update(0, deltaTime, faceRight, 0.2);
		fireeffect3.setTextureRect(animationfire.xyRect);
		fireeffect3.setPosition(hitbox.getPosition().x+150, hitbox.getPosition().y - 50);
	}


	if (changeFade == true) {
		colorValue += deltaTime * 100;
	}
	else if (changeFade == false) {
		colorValue -= deltaTime * 100;
	}

	if (colorValue >= 150) {
		colorValue = 150;
		changeFade = false;
	}
	else if (colorValue <= 0) {
		colorValue = 0;
		changeFade = true;
	}

	areabox.setFillColor(Color(255, 255, 0, colorValue));
	areabox.setOutlineColor(Color(255, 255, 0, colorValue));

}

void Tank::Draw(RenderTarget& target)
{
	if (isAlive == true && mode == 1) 
	{
		if (isAppearArea == true) {
			if (isRange == false) {
				target.draw(areabox);
			}
		}

		//target.draw(areabox2);
		target.draw(hpbarbox);
		target.draw(hpbar);
	}



	target.draw(body);
	//target.draw(hitbox);

	if (isAlive == false)
	{
		target.draw(fireeffect);
		target.draw(fireeffect2);
		target.draw(fireeffect3);
		if (animationbomb.isAnimationDoneTank() == false) {
			target.draw(bombeffect1);
		}
	}

}

void Tank::DrawUI(RenderTarget& target)
{
	if (isAlive == true && mode ==0)
	{
		target.draw(hpbarbox);
		target.draw(hpbar);
	}
}
