#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <fstream>
#include "Animation.h"
#include "Player.h"
#include "Ally.h"
#include "Enemy.h"
#include "Tank.h"
#include "Tower.h"
#include "Platform.h"
#include "BulletPlayer.h"
#include "BulletBot.h"
#include "Button.h"
#include "Item.h"
#include "Bomb.h"
#include "Plane.h"
#include "PauseMenu.h"
#include "Windmill.h"
#include "Effect.h"
#include "Fade.h"

using namespace sf;
using namespace std;

class State
{
public:

	//Constructor/Destructor
	State(RenderWindow* window, stack<State*>* states);
    virtual ~State();

	const bool& getQuit() const { return isQuit; };
	const bool getKeyTime();
	void endState() { isQuit = true; }
	void pauseState() { isPause = true; }
	void unpauseState() { isPause = false; }
	void initial();

	//Functions
	virtual void UpdateMousePositions();
	virtual void UpdateKeytime(const float& deltaTime);
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void Update(const float& deltaTime, Event evnt) = 0;
	virtual void Render(RenderTarget* target = nullptr) = 0;
	void ChangeFadeText(const float& deltaTime);
	void CheckGameover(const float& deltaTime);
	void CheckGamewin(const float& deltaTime);
	void AirsupportFadeText(const float& deltaTime);
	void UpdateScore();
	void UpdateKill(const float& deltaTime);
	void UpdateKillstreak();
	void UpdateScoreboard();
	void UpdateScoreboardwithKill();

	void UpdateNameKillScore();
	void GetNameKillScore();
	int Random(int max);

	int score = 0;
	Font font;

protected:

	Text tankname;


	int kill = 0;
	int killstreak = 0;
	int endstreak = 5;
	int Tempkill = 0;
	int TempAnotherkill = 0;
	float counterkill = 0;
	int scorestreak = 0;
	bool isKillstreak = false;

	Text killText;
	Text killstreakText;

	float totalTimetutorial;

	bool isEnd;

	bool isAirsupport = false;
	bool isAirstrike = false;
	bool isGameover;
	bool isAppear;
	bool isAppear2;
	bool isContinue;
	bool isContinue2;

	float colorValue;
	bool changeFade;

	float counter;
	Text continueText;
	Text continueText2;

	Text scoreTexts[5];
	Text nameTexts[5];
	Text scoreboardText;
	int scores[5];
	string names[5];
	Text killTexts[5];

	int kills[5];
	Text airSupportText;

	bool isWrite;

	string playername;
	ofstream writefile;
	ifstream readfile;

	RectangleShape black;

	Fade* fade;

	bool isInitial;

	float keyTime;
	float keyTimeMax;

	View view;

	PauseMenu* pauseMenu;

	int randommode = 0;
	int randomshoot1 = 0;
	int randomshoot2 = 0;
	float totalTime = 0.f;
	float totaltotal = 0.f;
	float randomSwitch = 0.f;

	float totalTimemode = 0.f;

	stack<State*>* states;
	RenderWindow* window;

	ostringstream ssScore;

	Text scoreText;
	Text objectiveText;
	Text gameover;
	Text accomplish;
	Text mission;

	Text stage1Text;
	Text stage2Text;
	Text finalstageText;
	Text victoryText;


	bool isQuit;
	bool isPause;

	//For Inherited Class
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	SoundBuffer click;
	Sound clicksound;

	SoundBuffer type;
	Sound typesound;


private:
	
};

