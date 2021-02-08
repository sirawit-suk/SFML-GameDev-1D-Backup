#include "Windmill.h"

Windmill::Windmill(Texture* texture, Texture* wing, Texture* flag, Vector2u imageCount, float switchTime, float speed, Vector2f setPosition)
	:animation(flag, imageCount)
{

	row = 0;
	this->speed = speed;
	this->switchTime = switchTime;
	this->velocity.x = 0;
	this->velocity.y = 0;

	this->isActiveEnemy = false;
	this->isActiveAlly = false;

	basebody.setSize(Vector2f(500, 500));
	basebody.setOrigin((basebody.getSize().x / 2.f), (basebody.getSize().y / 2.f));
	basebody.setPosition(setPosition);
	basebody.setTexture(texture);

	wingbody.setSize(Vector2f(500, 500));
	wingbody.setOrigin((wingbody.getSize().x / 2.f), (wingbody.getSize().y / 2.f));
	wingbody.setPosition(setPosition.x, setPosition.y-50);
	wingbody.setTexture(wing);

	hitbox.setSize(Vector2f(900.f, 450.f));
	hitbox.setOrigin((hitbox.getSize().x / 2.f), (hitbox.getSize().y / 2.f));
	hitbox.setPosition(setPosition.x, setPosition.y +480);
	hitbox.setOutlineThickness(1.f);

	flagTotal = 0;
	flagRed = 0;
	flagBlue = 0;

	totalTime = 0;

	flagbar.setFillColor(Color(255, 0, 0, 240));
	flagbar.setSize(Vector2f(flagTotal, 20));
	flagbar.setPosition(wingbody.getPosition().x-400, wingbody.getPosition().y-150);

	flagbarbox.setSize(Vector2f(800 , 20));
	flagbarbox.setFillColor(Color(200, 200, 200, 100));
	flagbarbox.setOutlineColor(Color(0, 0, 0, 150));
	flagbarbox.setOutlineThickness(2);
	flagbarbox.setPosition(flagbar.getPosition().x, flagbar.getPosition().y);

	flagbody.setSize(Vector2f(60*2, 60*2));
	flagbody.setOrigin((basebody.getSize().x / 2.f), (basebody.getSize().y / 2.f));
	flagbody.setTexture(flag);

	pole.setSize(Vector2f(5, 250));
	pole.setOrigin((basebody.getSize().x / 2.f), (basebody.getSize().y / 2.f));
	pole.setFillColor(Color(97, 75, 56, 240));
	pole.setOutlineThickness(1);
	pole.setOutlineColor(Color(97-20, 75-20, 56-20,255));
	pole.setPosition(Vector2f(hitbox.getPosition().x, hitbox.getPosition().y- hitbox.getSize().y/2-20));

	isComplete = false;
}

Windmill::~Windmill()
{
}

void Windmill::Update(const float& deltaTime)
{
	if(isComplete == false)
	{
		if (isActiveEnemy == false && isActiveAlly == false) {	//None Capture
			hitbox.setFillColor(Color(255, 255, 255, 20));
			hitbox.setOutlineColor(Color(255, 255, 255, 60));
		}
		else if (isActiveEnemy == true && isActiveAlly == false) {	//Enemy Capture
			hitbox.setFillColor(Color(255, 0, 0, 20));
			hitbox.setOutlineColor(Color(255, 0, 0, 60));
			flagTotal -= deltaTime * 50;	//*50
		}
		else if (isActiveAlly == true && isActiveEnemy == false) {	//Ally Capture
			hitbox.setFillColor(Color(0, 255, 0, 20));
			hitbox.setOutlineColor(Color(0, 255, 0, 60));
			flagTotal += deltaTime * 50;	//*50
		}
		else if (isActiveEnemy == true && isActiveAlly == true) {	//Both Capture
			hitbox.setFillColor(Color(255, 255, 0, 20));
			hitbox.setOutlineColor(Color(255, 255, 0, 60));
		}

		isActiveAlly = false;
		isActiveEnemy = false;

		//flagTotal Blue ++ // Red --

		if (flagTotal > 0) {	//Blue & RED
			if (flagTotal > 800) {
				flagTotal = 800;
			}
			flagbar.setSize(Vector2f(abs(flagTotal), 20));
			flagbar.setFillColor(Color(0, 0, abs(flagTotal / 8) + 150, 240));

			row = 0;
		}
		else if (flagTotal < 0) {
			if (flagTotal < -800) {
				flagTotal = -800;
			}
			flagbar.setSize(Vector2f(abs(flagTotal), 20));
			flagbar.setFillColor(Color(abs(flagTotal / 8) + 150, 0, 0, 240));


			row = 1;
		}

		if (flagTotal >= 800)
		{
			isComplete = true;
		}
	}

	flagbody.setPosition(Vector2f(hitbox.getPosition().x, hitbox.getPosition().y - flagbody.getSize().y / 2 - abs(flagTotal / 3.5)));

	angle = speed * deltaTime;
	wingbody.rotate(angle);

	animation.Update(row, deltaTime, 1, switchTime);
	flagbody.setTextureRect(animation.xyRect);

}

void Windmill::Draw(RenderTarget& target)
{
	target.draw(flagbarbox);
	target.draw(flagbar);

	target.draw(basebody);
	target.draw(wingbody);
	target.draw(hitbox);

	target.draw(pole);
	if (flagTotal != 0) {
		target.draw(flagbody);
	}



}
