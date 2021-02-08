#include "State.h"

State::State(RenderWindow* window, stack<State*>* states)
{
	font.loadFromFile("Resource/Font/futura medium bt.ttf");

	click.loadFromFile("Resource/Sound/clicksound.wav");
	clicksound.setBuffer(click);
	clicksound.setVolume(10);

	type.loadFromFile("Resource/Sound/typesound.wav");
	typesound.setBuffer(type);
	typesound.setVolume(10);

	srand(time(NULL));

	ssScore << "SCORE : " << score;
	scoreText.setFont(font);
	scoreText.setLetterSpacing(2);
	scoreText.setFillColor(Color::White);
	scoreText.setCharacterSize(30);
	scoreText.setPosition(Vector2f(1600, 10));
	scoreText.setString(ssScore.str());

	killText.setFont(font);
	killText.setString("KILL : "+ to_string(kill));
	killText.setFillColor(Color::White);
	killText.setLetterSpacing(2);
	killText.setCharacterSize(30);
	killText.setPosition(Vector2f(1645, 50));

	killstreakText.setFont(font);
	killstreakText.setFillColor(Color::Yellow);
	killstreakText.setLetterSpacing(2);
	killstreakText.setCharacterSize(30);
	killstreakText.setPosition(Vector2f(1350, 90));
	

	objectiveText.setFont(font);
	objectiveText.setString("MAIN OBJECTIVE : CAPTURE THE FLAG");
	objectiveText.setFillColor(Color::White);
	objectiveText.setLetterSpacing(2);
	objectiveText.setCharacterSize(20);
	objectiveText.setPosition(Vector2f(20, 300));

	airSupportText.setFont(font);
	airSupportText.setString("AIR SUPPORT IS COMING");
	airSupportText.setLetterSpacing(2);
	airSupportText.setFillColor(Color::Red);
	airSupportText.setOutlineColor(Color(180,0,0,255));
	airSupportText.setOutlineThickness(1);
	airSupportText.setCharacterSize(30);
	airSupportText.setPosition(Vector2f(1450, 130));

	gameover.setFont(font);
	gameover.setString("DEFEAT");
	gameover.setFillColor(Color::White);
	gameover.setLetterSpacing(2);
	gameover.setCharacterSize(200);
	gameover.setOrigin(gameover.getGlobalBounds().width / 2, gameover.getGlobalBounds().top / 2);
	gameover.setPosition(Vector2f(window->getSize().x/2, window->getSize().y / 2 - 100));

	accomplish.setFont(font);
	accomplish.setString("ACCOMPLISHED");
	accomplish.setFillColor(Color::White);
	accomplish.setLetterSpacing(2);
	accomplish.setCharacterSize(130);
	accomplish.setOrigin(accomplish.getGlobalBounds().width / 2, accomplish.getGlobalBounds().top / 2);
	accomplish.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2+80));
	
	mission.setFont(font);
	mission.setString("MISSION");
	mission.setFillColor(Color::White);
	mission.setLetterSpacing(2);
	mission.setCharacterSize(200);
	mission.setOrigin(mission.getGlobalBounds().width / 2, mission.getGlobalBounds().top / 2);
	mission.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2-120));


	stage1Text.setFont(font);
	stage1Text.setString("STAGE 1");
	stage1Text.setFillColor(Color::White);
	stage1Text.setLetterSpacing(2);
	stage1Text.setCharacterSize(200);
	stage1Text.setOrigin(stage1Text.getGlobalBounds().width / 2, stage1Text.getGlobalBounds().top / 2);
	stage1Text.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2 - 100));

	stage2Text.setFont(font);
	stage2Text.setString("STAGE 2");
	stage2Text.setFillColor(Color::White);
	stage2Text.setLetterSpacing(2);
	stage2Text.setCharacterSize(200);
	stage2Text.setOrigin(stage2Text.getGlobalBounds().width / 2, stage2Text.getGlobalBounds().top / 2);
	stage2Text.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2-100));

	finalstageText.setFont(font);
	finalstageText.setString("FINAL STAGE");
	finalstageText.setFillColor(Color::White);
	finalstageText.setLetterSpacing(2);
	finalstageText.setCharacterSize(200);
	finalstageText.setOrigin(finalstageText.getGlobalBounds().width / 2, finalstageText.getGlobalBounds().top / 2);
	finalstageText.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2 - 100));

	victoryText.setFont(font);
	victoryText.setString("VICTORY");
	victoryText.setFillColor(Color::White);
	victoryText.setLetterSpacing(2);
	victoryText.setCharacterSize(200);
	victoryText.setOrigin(victoryText.getGlobalBounds().width / 2, victoryText.getGlobalBounds().top / 2);
	victoryText.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2 - 100));

	this->window = window;
	this->states = states;
	this->isQuit = false;
	this->isPause = false;

	this->changeFade = false;
	this->isGameover = false;
	this->isAppear = false;
	this->isContinue = false;
	this->isContinue2 = false;
	this->isEnd = false;
	colorValue = 255.f;

	this->totalTimetutorial = 0;

	this->totalTime = 0;

	//PauseMenu
	pauseMenu = new PauseMenu(*window, font, view);
	fade = new Fade(*window);

	this->keyTime = 0.f;
	this->keyTimeMax = 1.f;

	isInitial = true;

	black.setSize(Vector2f(window->getSize()));
	black.setPosition(Vector2f(window->getPosition()));
	black.setFillColor(Color::Black);

	playername = " ";
	isWrite = false;

    counter = 0.f;

	continueText.setFont(font);
	continueText.setString("PRESS ENTER TO EXIT");
	continueText.setFillColor(Color::White);
	continueText.setLetterSpacing(2);
	continueText.setCharacterSize(50);
	continueText.setOrigin(continueText.getGlobalBounds().width/2, continueText.getGlobalBounds().height/2);
	continueText.setPosition(Vector2f(window->getSize().x/2, window->getSize().y - 200));

	continueText2.setFont(font);
	continueText2.setString("PRESS ENTER TO CONTINUE");
	continueText2.setFillColor(Color::White);
	continueText2.setLetterSpacing(2);
	continueText2.setCharacterSize(50);
	continueText2.setOrigin(continueText2.getGlobalBounds().width / 2, continueText2.getGlobalBounds().height / 2);
	continueText2.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y - 200));
	
	tankname.setFont(font);
	tankname.setFillColor(Color::White);
	tankname.setCharacterSize(27);
	tankname.setLetterSpacing(2);
	tankname.setPosition(Vector2f(960, 962));
	
}

State::~State()
{

}

const bool State::getKeyTime()
{
	if (keyTime >= keyTimeMax) 
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

void State::initial()
{
	fade = new Fade(*window);
}

void State::UpdateMousePositions()
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(Mouse::getPosition(*window));
}

void State::UpdateKeytime(const float& deltaTime)
{
	if (keyTime < keyTimeMax) 
	{
		keyTime += 4*deltaTime;
	}
}

void State::ChangeFadeText(const float& deltaTime)
{
	if (changeFade == true) {
		colorValue += deltaTime * 400;
	}
	else if (changeFade == false) {
		colorValue -= deltaTime * 400;
	}

	if (colorValue >= 255) {
		colorValue = 255;
		changeFade = false;
	}
	else if (colorValue <= 0) {
		colorValue = 0;
		changeFade = true;
	}
}

void State::AirsupportFadeText(const float& deltaTime)
{
	if (isAirsupport == true) {
		counter += deltaTime;
		ChangeFadeText(deltaTime);
		airSupportText.setFillColor(Color(255,0, 0, colorValue));
		airSupportText.setOutlineColor(Color(200, 0, 0, colorValue));
	}
	else {
		airSupportText.setFillColor(Color(1, 0, 0, 0));
		airSupportText.setOutlineColor(Color(1, 0, 0, 0));
	}
	
}

void State::CheckGameover(const float& deltaTime)
{
	if (isGameover == true) {
		counter += deltaTime;
		if (counter >= 5) {
			ChangeFadeText(deltaTime);
			isAppear = true;
		}
		continueText.setFillColor(Color(255, 255, 255, colorValue));
	}
	else {
		continueText.setFillColor(Color(1, 1, 1, 0));
	}
}

void State::CheckGamewin(const float& deltaTime)
{
	if (isEnd == true) {
		counter += deltaTime;
		if (counter >= 5) {
			ChangeFadeText(deltaTime);
			isAppear2 = true;
		}
		continueText.setFillColor(Color(255, 255, 255, colorValue));
	}
	else {
		continueText.setFillColor(Color(1, 1, 1, 0));
	}
}

void State::UpdateScore()
{
	ssScore.str("");
	ssScore << "SCORE : " << score;
	scoreText.setString(ssScore.str());
}

void State::UpdateKill(const float& deltaTime)
{


	killstreak = kill - Tempkill;
	totaltotal += deltaTime;
	if (totaltotal <= 5) {
		Tempkill = kill;
		killstreak = 0;
	}
	if (TempAnotherkill != kill) {
	
		if (killstreak >5) {
			endstreak += 1;
		}
		else if (killstreak >= 4) {
			endstreak += 2;
		}
		else if (killstreak >=2) {
			endstreak += 3;
		}
	}
	if (counterkill >= endstreak) {
		endstreak = 5;
		counterkill = 0;
		if (killstreak >= 2) {
			score += scorestreak;
			UpdateScore();
		}
		Tempkill = kill;
	}
	if (killstreak >= 2) {
		scorestreak = killstreak * 100;
		isKillstreak = true;
	}
	else
	{
		scorestreak = 0;
		isKillstreak = false;
	}
	if (killstreak >= 1) {
		counterkill += deltaTime;
	}
	
		TempAnotherkill = kill;


	killText.setString("KILL : " + to_string(kill));
}

void State::UpdateKillstreak()
{
	killstreakText.setString("KILL " + to_string(killstreak) + " STREAK BONUS +" + to_string(scorestreak));
}

void State::UpdateScoreboard()
{
	readfile.open("Resource/Text/player.ini");
	if (readfile.is_open())
	{
		readfile >> playername;
	}
	readfile.close();

	readfile.open("Resource/Text/score.ini");
	if (readfile.is_open())
	{
		for (size_t i = 0; i < 5; i++) {
			readfile >> names[i] >> kills[i] >> scores[i];
		}
		
	}
	readfile.close();

	isWrite = false;

	writefile.open("Resource/Text/score.ini");
	if (writefile.is_open())
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (score > scores[i] && isWrite == false) 
			{
				writefile << playername << " " << kill << " " << score << endl;
				isWrite = true;
			}

			writefile << names[i] << " " << kills[i] << " " << scores[i] << endl;

			if (score == scores[i] && isWrite == false)
			{
				writefile << playername << " " << kill << " " << score << endl;
				isWrite = true;
			}
		}
	}
	writefile.close();

}

void State::UpdateScoreboardwithKill()
{
	GetNameKillScore();

	readfile.open("Resource/Text/score.ini");
	if (readfile.is_open())
	{
		for (size_t i = 0; i < 5; i++) {
			readfile >> names[i] >> kills[i] >> scores[i];
		}

	}
	readfile.close();

	isWrite = false;

	writefile.open("Resource/Text/score.ini");
	if (writefile.is_open())
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (score > scores[i] && isWrite == false)
			{
				writefile << playername << " " << kill << " " << score << endl;
				isWrite = true;
			}

			writefile << names[i] << " " << kills[i] << " " << scores[i] << endl;

			if (score == scores[i] && isWrite == false)
			{
				writefile << playername << " " << kill << " " << score << endl;
				isWrite = true;
			}
		}
	}
	writefile.close();
}

void State::UpdateNameKillScore()
{
	writefile.open("Resource/Text/current.ini");
	if (writefile.is_open())
	{
		writefile << playername << " " << kill << " " << score << endl;
	}
	writefile.close();
}

void State::GetNameKillScore()
{
	readfile.open("Resource/Text/current.ini");
	if (readfile.is_open())
	{
		readfile >> playername >> kill >> score;
	}
	readfile.close();
}

int State::Random(int max)
{
	return  rand() % max;
}
