#include "Button.h"

Button::Button(float x, float y, float width, float height,
	Font* font, string text,
	Color idleColor, Color hoverColor, Color ActiveColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setLetterSpacing(1.5);
	this->text.setCharacterSize(35);
	this->text.setPosition(
		this->shape.getPosition().x + ((this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f) -5,
		this->shape.getPosition().y + ((this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f) -5
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

Button::~Button()
{
}

const bool Button::isHovered() const
{
	if (this->buttonState == BTN_HOVER)
		return true;
	return false;
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

void Button::Update(const Vector2f mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}

void Button::Draw(RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
