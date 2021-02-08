#include "Animation.h"

Animation::Animation(Texture* texture, Vector2u imageCount)
	:imageCount(imageCount)
{
	totalTime = 0.f;
	currentImage.x = 0;

	xyRect.width = texture->getSize().x / (float)imageCount.x;
	xyRect.height = texture->getSize().y / (float)imageCount.y;

	isDone = false;
	isDonetank = false;
}

Animation::~Animation(){ }

void Animation::Update(int row, float deltaTime, bool faceRight, float switchTime)
{
	if (rowTemp != row) {
		currentImage.x = 0;
	}
	rowTemp = row;

	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	xyRect.top = currentImage.y * xyRect.height;

	if (faceRight) 
	{
		xyRect.left = currentImage.x * xyRect.width;
		xyRect.width = abs(xyRect.width);
	}
	else
	{
		xyRect.left = (currentImage.x + 1) * abs(xyRect.width);
		xyRect.width = -abs(xyRect.width);
	}
	
	if (currentImage.x == 30 && currentImage.y == 2) {
		isDone = true;
	}
	if (currentImage.x == 27 && currentImage.y == 0) {
		isDonetank = true;
	}

}
