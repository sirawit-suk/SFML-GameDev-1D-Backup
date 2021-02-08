#pragma once
#include "State.h"
#include "ScoreboardState.h"
#include "LoadingState.h"

class GameState : public State
{
public:

	GameState(RenderWindow* window, stack<State*>* states);
	virtual ~GameState();

	//Functions
	void UpdatePauseMenuButton();
	void SetDialogText(string dialog);

	void AllIntroduction();
	void State1();
	void Initial_State1();
	void State2();
	void Initial_State2();

	void UpdateInput(const float& deltaTime);
	void UpdatePlayerInput(const float& deltaTime);
	void UpdateMouseAimPosition();

	void UpdateBullet(const float& deltaTime);
	void Update(const float& deltaTime, Event evnt);

	void UpdateCollision(const float& deltaTime);
	void UpdateDelete(const float& deltaTime);
	
	void CameraView();
	void Render(RenderTarget* target = nullptr);

private:

	bool isHover0;
	bool isHover1;

	bool isBegin;
	bool isAlreadyDropItem;
	bool isAlreadyBomb;
	bool isAlready1;
	bool isAlready9;
	bool isAlready11;
	bool isAlreadyMoveTank;
	bool isAlready21;
	bool isAlready28;
	bool isAlready32;
	int isAlreadyCollect;

	int Airsupport = 0;

	int randomNum = 10;
	//Sound
	SoundBuffer sf_plane;
	Sound soundeffect_plane1;
	Sound soundeffect_plane2;

	SoundBuffer sf_planeb1;
	SoundBuffer sf_planeb2;
	SoundBuffer sf_planeb3;
	Sound soundeffect_planebomb[3];


	Texture windmillTexture;
	Texture wingTexture;
	Texture flag;

	vector <Windmill> windmills;

	Music introductionsound;
	Music battlesound;
	Music backgroundsound;
	
	//View States

	bool view1 = false;
	bool view2 = false;
	bool view3 = false;

	float calibrate = 0.f;


	Texture bombTexture;
	Texture fireTexture;

	Texture towerTexture;
	vector <Tower> towers;
	vector <Tower> towers2;

	Texture allytankTexture;
	vector <Tank> tanks_ally;
	Texture enemytankTexture;
	vector <Tank> tanks_enemy; 

	Texture platformTexture;
	Texture obstructTexture;
	vector <Platform> platforms;

	Texture bulletTexture;
	vector <BulletPlayer> bullets;
	vector <BulletBot> bullets_enemy;
	vector <BulletBot> bullets_ally;

	Texture allyTexture;
	Texture allyTexture2;
	vector <Ally> allys;
	Texture enemyTexture;
	Texture enemyTexture2;
	vector <Enemy> enemys;
	
	Texture townsendTexture;

	Texture firstaidTexture;
	vector <Item> firstaids;
	Texture armorTexture;
	vector <Item> armors;
	Texture gunTexture;
	vector <Item> guns;
	Texture airsupportTexture;
	vector <Item> airsupports;
	Texture healtankTexture;
	vector <Item> healtanks;

	Texture enemyplaneTexture;
	vector <Plane> planes_enemy;
	Texture allyplaneTexture;
	vector <Plane> planes_ally;

	Texture planeBackground1;
	Texture planeBackground2;
	vector <Plane> planes_ally_bg;
	vector <Plane> planes_enemy_bg;

	Texture ef_bomb;
	vector <Effect> bombeffects;
	Texture bombTexture1;
	vector <Bomb> bombs1;
	Texture ef_blood;
	vector <Effect> bloodeffects;

	int randomshoot;
	int randommode;

	int mode;

	Texture townsendhumanTexture;
	RectangleShape townsend;

	Text dialogText;
	Text pleaseEnter;
	string dialog[34];

	int dialogNum = 0; // 0

		//Game States
	int gameMode = 0; //0
	bool gameMode_isInitial = false;

	float countergameMode1 = 0.f;
	float countergameMode2 = 0.f;

	RectangleShape dialogbox;

	Texture playerTexture;
	Player* player;
	Ally* townsendhuman;

	Texture bg_Floor;
	RectangleShape backgroundFloor;

	Texture bg_Sky;
	RectangleShape backgroundSky;

	Texture bg_Tree;
	RectangleShape backgroundTree1;
	RectangleShape backgroundTree2;
	RectangleShape backgroundTree3;
	RectangleShape backgroundTree4;

	Vector2f aimDir;
	Vector2f aimDirNorm;

	//Sounds
	//Because I have problem about sound in Enemy vector so i put it in here
	SoundBuffer sf_shoot;
	Sound soundeffect_shoot;

	SoundBuffer sf_tankgun;
	Sound soundeffect_tankgun;

	SoundBuffer sf_collectgun;
	Sound soundeffect_collectgun;

	SoundBuffer sf_collectfirst;
	Sound soundeffect_collectfirst;

	SoundBuffer sf_cheer;
	Sound soundeffect_cheer;

	SoundBuffer sf_bomb;
	Sound soundeffect_bomb;

	SoundBuffer sf_ticking;
	Sound soundeffect_ticking;

	SoundBuffer sf_tankexp;
	Sound soundeffect_tankexposion;

	SoundBuffer sf_tankbullethit;
	Sound soundeffect_tankbullethit;

	SoundBuffer sf_letgo;
	Sound soundeffect_letgo;

	SoundBuffer sf_dead[4];
	Sound soundeffect_dead[4];

	SoundBuffer sf_tankmove;
	Sound soundeffect_tankmove;

	SoundBuffer sf_allytalk[5];
	Sound soundeffect_allytalk[5];


	SoundBuffer sf_germantalk[5];
	Sound soundeffect_germantalk[5];
};

