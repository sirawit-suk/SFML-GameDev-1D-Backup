#include "Fade.h"

Fade::Fade(RenderWindow& window)
{
	fade.setSize(Vector2f(window.getSize()));
	fade.setPosition(Vector2f(window.getPosition()));
	fade.setFillColor(Color(0, 0, 0, 0));

	fadeValue = 255.f;
	isFade = false;
	isBright = true;
	isFadeDone = false;
	isBrightDone = false;

	setValue = 70.f;
	a = 1.f;
}

Fade::~Fade()
{
}

void Fade::Update(const float& deltaTime)
{
	if (isBright == true && isFade == true) {
		isBright = false;
	}

	if (fadeValue > 0 && isBright == true) {

		a += deltaTime*2;
		fadeValue -= setValue*a * deltaTime;
		if (fadeValue < 0.f) {
			fadeValue = 0.f;
			isBrightDone = true;
			isBright = false;
		}
		fade.setFillColor(Color(0, 0, 0, fadeValue));
	}


	if (fadeValue < 255.f && isFade == true) {

		a += deltaTime*2;
		fadeValue += setValue*a * deltaTime;
		if (fadeValue > 255.f) {
			fadeValue = 255.f;
			isFadeDone = true;
			isFade = false;
		}
		fade.setFillColor(Color(0, 0, 0, fadeValue));
	}
}

void Fade::Draw(RenderTarget& target)
{
	target.draw(fade);
}
