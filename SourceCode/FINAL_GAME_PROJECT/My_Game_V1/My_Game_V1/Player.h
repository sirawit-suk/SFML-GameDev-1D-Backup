#pragma once
#include "Human.h"

class Player : public Human
{
public:

	//Constructor/Destructor
	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~Player();

	//Functions
	void PlayerInput();
	void Update(const float& deltaTime, Vector2f aimDir);
	void Draw(RenderTarget& target); //RenderWindow& window
	void DrawUI(RenderTarget& target);

	bool isNewgun;
	bool isOut;
	bool isStop;
	
	float totalTime;

	

private:

	ifstream readfile;
	string playername;

	Text playerText;


	int mode;
	int rowUpgrade;

	//UI 
	RectangleShape profile;
	Texture pf;

	RectangleShape gunbox;

	RectangleShape gun1;
	Text gunText1;
	Texture g1;
	RectangleShape gun2;
	Text gunText2;
	Texture g2;

	Text hpText;
	Text armorText;

	float sizegun;

	//Players
	Animation animation;
};

