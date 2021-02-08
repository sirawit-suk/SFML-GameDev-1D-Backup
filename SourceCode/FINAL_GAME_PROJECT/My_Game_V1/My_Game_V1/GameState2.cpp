#include "GameState2.h"

GameState2::GameState2(RenderWindow* window, stack<State*>* states) : State(window, states)
{
	randommode = 0;
	randomshoot = 0;
	score = 0;

	//Background Music
	battlesound.openFromFile("Resource/Sound/battlesound.wav");
	battlesound.setVolume(100);
	battlesound.setLoop(1);

	backgroundsound.openFromFile("Resource/Sound/backgroundsoundgame1.wav");
	backgroundsound.setVolume(40);
	backgroundsound.setLoop(1);

	//Sound Plane
	sf_plane.loadFromFile("Resource/Sound/planesound.wav");
	soundeffect_plane1.setBuffer(sf_plane);
	soundeffect_plane1.setVolume(20);
	soundeffect_plane2.setBuffer(sf_plane);
	soundeffect_plane2.setVolume(20);

	sf_planeb1.loadFromFile("Resource/Sound/planebombsound1.wav");
	sf_planeb2.loadFromFile("Resource/Sound/planebombsound2.wav");
	sf_planeb3.loadFromFile("Resource/Sound/planebombsound3.wav");
	soundeffect_planebomb[0].setBuffer(sf_planeb1);
	soundeffect_planebomb[1].setBuffer(sf_planeb2);
	soundeffect_planebomb[2].setBuffer(sf_planeb3);
	soundeffect_planebomb[0].setVolume(50);
	soundeffect_planebomb[1].setVolume(40);
	soundeffect_planebomb[2].setVolume(40);

	//LoadFromFile Texture & Sound
	platformTexture.loadFromFile("Resource/Component/platform.png");
	obstructTexture.loadFromFile("Resource/Component/OBSTRUCT_SHEET.png");

	townsendTexture.loadFromFile("Resource/Picture/townsend.png");
	townsend.setTexture(&townsendTexture);
	townsend.setSize(Vector2f(600 / 3.5, 700 / 3.5));
	townsend.setPosition(100, 900);

	dialogbox.setSize(Vector2f(window->getSize().x, 700 / 2.5));
	dialogbox.setFillColor(Color(0, 0, 0, 220));
	dialogbox.setPosition(0, 900);

	readfile.open("Resource/Text/current.ini");

	if (readfile.is_open())
	{
		readfile >> playername >> kill >> score;
	}
	readfile.close();

	dialog[0] = "Oh... I think we're here.";
	dialog[1] = "\"CAMBRAI TOWN\"";
	dialog[2] = "!!!";
	dialog[3] = "I think we got a very BIG PROBLEM.";
	dialog[4] = "We need to capture the last location which is an important strategic point.";
	dialog[5] = "If we succeed to control CAMBRAI TOWN, This war will be our VICTORIOUS!";
	dialog[6] = "But...";
	dialog[7] = "We have an Enemy tank \"BLOCK\" our way!";
	dialog[8] = "It has armor that we can't penetrate.";
	dialog[9] = "EXCEPT...";
	dialog[10] = "\"Air Strike\" !";
	dialog[11] = "You can call \"Air Strike\" by pickup the ITEMS when you kill enemies.";
	dialog[12] = "This is the ONLY WAY to damage the enemy tank.";
	dialog[13] = "So... We need to destroy the enemy tank before it slaughter us all.";
	dialog[14] = "The result of this battle will determine the fate of this world...";
	dialog[15] = "Good luck, " + playername + " !";
	dialog[16] = "";

	playerTexture.loadFromFile("Resource/Sprite/PLAYER_SHEET2.png");
	allyTexture.loadFromFile("Resource/Sprite/ALLY_SHEET.png");
	allyTexture2.loadFromFile("Resource/Sprite/ALLY_SHEET2.png");
	enemyTexture.loadFromFile("Resource/Sprite/ENEMY_SHEET.png");
	enemyTexture2.loadFromFile("Resource/Sprite/ENEMY_SHEET2.png");
	allytankTexture.loadFromFile("Resource/Sprite/TANK_SHEET.png");
	enemytankTexture.loadFromFile("Resource/Sprite/TANKENEMY_SHEET.png");

	bombTexture.loadFromFile("Resource/Effect/BOMBEFFECT2_SHEET.png"); //*******
	fireTexture.loadFromFile("Resource/Effect/FIREEFFECT_SHEET.png"); //*******

	towerTexture.loadFromFile("Resource/Component/TOWER_SHEET.png");

	bulletTexture.loadFromFile("Resource/Component/bullet.jpg");
	windmillTexture.loadFromFile("Resource/Component/windmill.png");
	wingTexture.loadFromFile("Resource/Component/wing.png");
	flag.loadFromFile("Resource/Component/FLAG.png");
	firstaidTexture.loadFromFile("Resource/Item/FIRSTAID_SHEET.png");
	armorTexture.loadFromFile("Resource/Item/ARMOR_SHEET.png");
	gunTexture.loadFromFile("Resource/Item/GUN_SHEET.png");
	airsupportTexture.loadFromFile("Resource/Item/AIRSUPPORT.png");
	airstrikeTexture.loadFromFile("Resource/Item/AIRSTRIKE.png");
	healtankTexture.loadFromFile("Resource/Item/HEALTANK_SHEET.png");

	enemyplaneTexture.loadFromFile("Resource/Sprite/PLANE_ENEMY_SHEET.png");
	allyplaneTexture.loadFromFile("Resource/Sprite/PLANE_ALLY_SHEET.png");
	planeBackground1.loadFromFile("Resource/Component/planebackground1.png");
	planeBackground2.loadFromFile("Resource/Component/planebackground2.png");
	ef_bomb.loadFromFile("Resource/Effect/BOMB_SHEET.png");
	bombTexture1.loadFromFile("Resource/Effect/BOMB2_SHEET.png");
	ef_blood.loadFromFile("Resource/Effect/BLOOD_SHEET.png");

	bg_Floor.loadFromFile("Resource/Background/backgroundFloor2.png");
	bg_Sky.loadFromFile("Resource/Background/backgroundSky.png");
	bg_Tree.loadFromFile("Resource/Background/backgroundTree.png");

	sf_shoot.loadFromFile("Resource/Sound/shoot_rifle.wav");
	soundeffect_shoot.setBuffer(sf_shoot);
	sf_tankgun.loadFromFile("Resource/Sound/shoot_tank.wav");
	soundeffect_tankgun.setBuffer(sf_tankgun);

	sf_collectgun.loadFromFile("Resource/Sound/collectgun.wav");
	soundeffect_collectgun.setBuffer(sf_collectgun);
	sf_collectfirst.loadFromFile("Resource/Sound/collectfirst.wav");
	soundeffect_collectfirst.setBuffer(sf_collectfirst);

	sf_cheer.loadFromFile("Resource/Sound/cheersound.wav");
	soundeffect_cheer.setBuffer(sf_cheer);

	sf_bomb.loadFromFile("Resource/Sound/bombsound.wav");
	soundeffect_bomb.setBuffer(sf_bomb);

	sf_ticking.loadFromFile("Resource/Sound/tickingbombsound.wav");
	soundeffect_ticking.setBuffer(sf_ticking);

	sf_tankexp.loadFromFile("Resource/Sound/tankexposionsound.wav");
	soundeffect_tankexposion.setBuffer(sf_tankexp);

	sf_tankbullethit.loadFromFile("Resource/Sound/tankbullethit.wav");
	soundeffect_tankbullethit.setBuffer(sf_tankbullethit);

	sf_letgo.loadFromFile("Resource/Sound/letgo.wav");
	soundeffect_letgo.setBuffer(sf_letgo);

	sf_dead[0].loadFromFile("Resource/Sound/dead1.wav");
	soundeffect_dead[0].setBuffer(sf_dead[0]);
	sf_dead[1].loadFromFile("Resource/Sound/dead2.wav");
	soundeffect_dead[1].setBuffer(sf_dead[1]);
	sf_dead[2].loadFromFile("Resource/Sound/dead3.wav");
	soundeffect_dead[2].setBuffer(sf_dead[2]);
	sf_dead[3].loadFromFile("Resource/Sound/dead4.wav");
	soundeffect_dead[3].setBuffer(sf_dead[3]);

	sf_tankmove.loadFromFile("Resource/Sound/tankmove.wav");
	soundeffect_tankmove.setBuffer(sf_tankmove);

	sf_germantalk[0].loadFromFile("Resource/Sound/germantalk1.wav");
	soundeffect_germantalk[0].setBuffer(sf_germantalk[0]);
	sf_germantalk[1].loadFromFile("Resource/Sound/germantalk2.wav");
	soundeffect_germantalk[1].setBuffer(sf_germantalk[1]);
	sf_germantalk[2].loadFromFile("Resource/Sound/germantalk3.wav");
	soundeffect_germantalk[2].setBuffer(sf_germantalk[2]);
	sf_germantalk[3].loadFromFile("Resource/Sound/germantalk4.wav");
	soundeffect_germantalk[3].setBuffer(sf_germantalk[3]);
	sf_germantalk[4].loadFromFile("Resource/Sound/germantalk5.wav");
	soundeffect_germantalk[4].setBuffer(sf_germantalk[4]);

	sf_allytalk[0].loadFromFile("Resource/Sound/allytalk1.wav");
	soundeffect_allytalk[0].setBuffer(sf_allytalk[0]);
	sf_allytalk[1].loadFromFile("Resource/Sound/allytalk2.wav");
	soundeffect_allytalk[1].setBuffer(sf_allytalk[1]);
	sf_allytalk[2].loadFromFile("Resource/Sound/allytalk3.wav");
	soundeffect_allytalk[2].setBuffer(sf_allytalk[2]);
	sf_allytalk[3].loadFromFile("Resource/Sound/allytalk4.wav");
	soundeffect_allytalk[3].setBuffer(sf_allytalk[3]);
	sf_allytalk[4].loadFromFile("Resource/Sound/allytalk5.wav");
	soundeffect_allytalk[4].setBuffer(sf_allytalk[4]);

	//View Size
	view.setSize(Vector2f(window->getSize()));

	backgroundSky.setSize(Vector2f(6400, 580));
	backgroundSky.setTexture(&bg_Sky);
	backgroundSky.setTextureRect(IntRect(0, 0, 6400, 214));
	bg_Sky.setRepeated(1);

	backgroundFloor.setSize(Vector2f(6400, 500));
	backgroundFloor.setTexture(&bg_Floor);
	backgroundFloor.setTextureRect(IntRect(0, 0, 6400, 206));
	bg_Floor.setRepeated(1);

	backgroundTree1.setSize(Vector2f(6400, 270));
	backgroundTree1.setTexture(&bg_Tree);
	backgroundTree1.setTextureRect(IntRect(0, 0, 6400, 250));
	bg_Tree.setRepeated(1);
	backgroundTree2.setSize(Vector2f(6400, 270));
	backgroundTree2.setTexture(&bg_Tree);
	backgroundTree2.setTextureRect(IntRect(0, 0, 6400, 250));
	bg_Tree.setRepeated(1);
	backgroundTree3.setSize(Vector2f(6400, 270));
	backgroundTree3.setTexture(&bg_Tree);
	backgroundTree3.setTextureRect(IntRect(0, 0, 6400, 250));
	bg_Tree.setRepeated(1);
	backgroundTree4.setSize(Vector2f(6400, 270));
	backgroundTree4.setTexture(&bg_Tree);
	backgroundTree4.setTextureRect(IntRect(0, 0, 6400, 250));
	bg_Tree.setRepeated(1);

	backgroundFloor.setOrigin(backgroundFloor.getSize().x / 2, backgroundFloor.getSize().y / 2);
	backgroundSky.setOrigin(backgroundSky.getSize().x / 2, backgroundSky.getSize().y / 2);
	backgroundTree1.setOrigin(backgroundFloor.getSize().x / 2, backgroundFloor.getSize().y / 2);
	backgroundTree2.setOrigin(backgroundFloor.getSize().x / 2, backgroundFloor.getSize().y / 2);
	backgroundTree3.setOrigin(backgroundFloor.getSize().x / 2, backgroundFloor.getSize().y / 2);
	backgroundTree4.setOrigin(backgroundFloor.getSize().x / 2, backgroundFloor.getSize().y / 2);

	backgroundFloor.setPosition(view.getCenter().x, view.getCenter().y + 287);
	backgroundSky.setPosition(view.getCenter().x, view.getCenter().y - 253);
	//backgroundTree1.setPosition(view.getCenter().x, view.getCenter().y + 70);
	backgroundTree2.setPosition(view.getCenter().x, view.getCenter().y + 70);
	backgroundTree3.setPosition(view.getCenter().x, view.getCenter().y + 70);
	backgroundTree4.setPosition(view.getCenter().x, view.getCenter().y + 70);
	backgroundFloor.setPosition(view.getCenter().x, view.getCenter().y + 287);

	//New Player
	player = new Player(&playerTexture, Vector2u(3, 12), 0.1f, 350);	//Speed player 350
	player->hp = 1000;
	player->armor = 700;

	tanks_ally.push_back(Tank(&allytankTexture, &bombTexture, &fireTexture, Vector2u(1, 3), Vector2u(28, 1), Vector2u(12, 1), 0.075f, 50.f, Vector2f(500, 600.f), 1)); //50
	tanks_enemy.push_back(Tank(&enemytankTexture, &bombTexture, &fireTexture, Vector2u(1, 3), Vector2u(28, 1), Vector2u(12, 1), 0.075f, 50.f, Vector2f(3000, 600.f), 0)); //50

	windmills.push_back(Windmill(&windmillTexture, &wingTexture, &flag, Vector2u(4, 2), 0.1f, 20, Vector2f(3000, 350)));

	//Platforms
	platforms.push_back(Platform(&platformTexture, Vector2f(16000 * 2.f, 1150.f), Vector2u(1, 1), true, Vector2f(0.f, 0.f), 0)); //Sky
	platforms.push_back(Platform(&platformTexture, Vector2f(16000 * 2.f, 10.f), Vector2u(1, 1), true, Vector2f(0.f, 1080.f), 0)); //Bottom
	platforms.push_back(Platform(&platformTexture, Vector2f(10.f, 2000.f), Vector2u(1, 1), true, Vector2f(-200.f, 0.f), 0)); //Left
	platforms.push_back(Platform(&platformTexture, Vector2f(10.f, 2000.f), Vector2u(1, 1), true, Vector2f(4000, 0.f), 0)); //Left

	//plane
	planes_ally_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(1000.f, 100.f), 2)); //ally size
	planes_ally_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(3000.f, 100.f + 100.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(5000.f, 100.f + 200.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(7000.f, 100.f + 100.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(2000.f, 100.f + 100.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(4000.f, 100.f + 200.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(6000.f, 100.f + 100.f), 2)); //ally size 
	planes_ally_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(8000.f, 100.f), 2)); //ally size 
	planes_enemy_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(1000.f, 100.f), 3)); //Enemy size
	planes_enemy_bg.push_back(Plane(&planeBackground1, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(3000.f, 100.f + 100.f), 3)); //Enemy size 
	planes_enemy_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 200.f, Vector2f(2000.f, 100.f + 100.f), 3)); //Enemy size 
	planes_enemy_bg.push_back(Plane(&planeBackground2, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 300.f, Vector2f(4000.f, 100.f + 200.f), 3)); //Enemy size 

	allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3000.f, 600.f), 0));
	allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3200.f, 630.f), 0));
	allys.push_back(Ally(&allyTexture2, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3400.f, 750.f), 1));
	allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3300.f, 800.f), 0));
	allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3150.f, 900.f), 0));

	towers.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(1550.f, 500.f), 0));
	towers2.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(1550.f, 950.f), 0));
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1700.f, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1500.f, 600.f), 2)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1700.f, 1050.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1500.f, 1050.f), 2)); //Left

	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(600.f, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(100.f, 800.f), 5)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1000.f, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(530.f, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(100.f, 600.f), 2)); //Left

	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(600.f, 1050.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1000.f, 1050.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(530.f, 1050.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(100.f, 1050.f), 2)); //Left

	towers.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(2550, 500.f), 0));
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1700 + 1000.f, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1500 + 1000.f, 600.f), 2)); //Left

	towers.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(3550, 500.f), 0));
	towers2.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(1550.f + 1000.f + 1000, 950.f), 0));
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1700 + 1000.f + 1000, 600.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1500 + 1000.f + 1000, 600.f), 2)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1700 + 1000.f + 1000.f, 1050.f), 6)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1500 + 1000.f + 1000.f, 1050.f), 2)); //Left

	//ALL MOTHER CONSTUCTIONS
	/*
	planes_enemy.push_back(Plane(&enemyplaneTexture, Vector2u(1, 1), 0.1f, 800.f, Vector2f(2000.f, 300.f), 0)); //enemy = 0
	planes_ally.push_back(Plane(&allyplaneTexture, Vector2u(1, 1), 0.1f, 800.f, Vector2f(0.f, 200.f), 1)); //ally = 1

	bombs1.push_back(Bomb(&bombTexture1, Vector2u(31, 4), 0.05f, 100, 1, Vector2f(100, 500), 0));
	bombs1.push_back(Bomb(&bombTexture1, Vector2u(31, 4), 0.05f, 100, 1, Vector2f(200, 600), 0));

	//Obstructs;
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(400.f, 800.f), 1)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(600.f, 800.f), 2)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(800.f, 800.f), 3)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1000.f, 800.f), 4)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1200.f, 800.f), 5)); //Left
	platforms.push_back(Platform(&obstructTexture, Vector2f(0, 0), Vector2u(1, 6), true, Vector2f(1400.f, 800.f), 6)); //Left

	towers.push_back(Tower(&towerTexture, &bombTexture, &fireTexture, Vector2u(28, 1), Vector2u(12, 1), 0.075f, Vector2f(1200.f, 600.f)));

		armors.push_back(Item(&armorTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(600, 100), 0));
		guns.push_back(Item(&gunTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(4000, 100), 1));
		firstaids.push_back(Item(&firstaidTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(1000, 100), 0));

		allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(600.f, 650.f)));

		enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(3000.f, 700.f)));
	}
	*/

	initial();
	fade->setValue = 5;

	isHover0 = false;
	isHover1 = false;

	isBegin = false;
	isEnd = false;
	isAlreadyDropItem = false;
	isAlreadyCollect = false;
	isAlready1 = false;
	isAlready9 = false;
	isAlready11 = false;
	isAlreadyMoveTank = false;
	isAlready21 = false;
	isAlready28 = false;
	isAlready32 = false;

	mode = 0;

	backgroundsound.play();

	UpdateScore();
}

GameState2::~GameState2()
{
	delete fade;
	delete pauseMenu;
	delete player;
	enemys.clear();
	allys.clear();
	tanks_ally.clear();
	tanks_enemy.clear();
	bullets.clear();
	bullets_enemy.clear();
	bullets_ally.clear();
	firstaids.clear();
	armors.clear();
	guns.clear();
	airsupports.clear();
	airstrikes.clear();
	healtanks.clear();
	planes_enemy.clear();
	planes_ally.clear();
	planes_ally_bg.clear();
	planes_enemy_bg.clear();
	bombeffects.clear();
	bombs1.clear();
	bloodeffects.clear();
	windmills.clear();
	platforms.clear();
	towers.clear();
	towers2.clear();
}

void GameState2::UpdatePauseMenuButton()
{
	if (pauseMenu->isButtonPressed(0) && getKeyTime()) {
		fade->isFade = true;
		mode = 0;
		unpauseState();
	}
	if (pauseMenu->isButtonPressed(1) && getKeyTime()) {
		fade->isFade = false;
		clicksound.play();
		if (gameMode == 1 || gameMode == 2) {
			backgroundsound.play();
			battlesound.play();
		}

		unpauseState();
	}

	if (pauseMenu->isButtonHovered(0) && isHover0 == false)
	{
		typesound.play();
		isHover0 = true;
	}
	else if (!pauseMenu->isButtonHovered(0))
	{
		isHover0 = false;
	}

	if (pauseMenu->isButtonHovered(1) && isHover1 == false)
	{
		typesound.play();
		isHover1 = true;
	}
	else if (!pauseMenu->isButtonHovered(1))
	{
		isHover1 = false;
	}

}

///////////////////////////////////////////// STATE # 0 ////////////////////////////////////////////////// 

void GameState2::SetDialogText(string dialog)
{
	dialogText.setFont(font);
	dialogText.setString(dialog);
	dialogText.setFillColor(Color::White);
	dialogText.setLetterSpacing(2);
	dialogText.setCharacterSize(30);
	dialogText.setPosition(Vector2f(350, 960));

	pleaseEnter.setFont(font);
	pleaseEnter.setString("PRESS ENTER TO CONTINUE...");
	pleaseEnter.setFillColor(Color::White);
	pleaseEnter.setLetterSpacing(2);
	pleaseEnter.setCharacterSize(20);
	pleaseEnter.setPosition(Vector2f(1500, 1050));
}

void GameState2::AllIntroduction()
{

	SetDialogText(dialog[dialogNum]);
	if (totalTimetutorial >= 5 && isAlready1 == false)
	{
		tanks_ally[0].isAppearArea = false;
		isBegin = true;
		isAlready1 = true;
	}
	
	if (dialogNum >= 16 && isBegin == true) {
		isBegin = false;
		for (Tower& tower : towers)
		{
			tower.isStart = true;
		}
		for (Tower& tower2 : towers2)
		{
			tower2.isStart = true;
		}
	}
	if (dialogNum >= 16) {
		gameMode = 1;
		tanks_ally[0].isAppearArea = true;
	}

}

///////////////////////////////////////////// STATE # 1 ////////////////////////////////////////////////// 

void GameState2::Initial_Final()
{
	tanks_ally[0].isAppearArea = true;
	//Initial State one...
	if (backgroundsound.getStatus() == 0) { backgroundsound.play(); }
	soundeffect_cheer.play();
	soundeffect_letgo.play();

	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 550.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 600.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 650.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 700.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 750.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(5000.f, 800.f), 0));

	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 550.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 600.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 650.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 700.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 750.f), 0));
	enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(6000.f, 800.f), 0));

	bombs1.push_back(Bomb(&bombTexture1, Vector2u(31, 4), 0.05f, 100, 1, Vector2f(4850, 860.f), 0));

	windmills[0].flagTotal = -800;
}

void GameState2::FinalState()
{
	if (planes_enemy.size() < 1) {
		planes_enemy.push_back(Plane(&enemyplaneTexture, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 800.f, Vector2f(13000, 300.f), 0)); //enemy = 0
		planes_enemy.push_back(Plane(&enemyplaneTexture, &bombTexture, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 800.f, Vector2f(6000, 400), 0)); //enemy = 0
	}

	if (gameMode_isInitial == false) {
		Initial_Final();
		gameMode_isInitial = true;
	}

	if (tanks_ally[0].GetPosition().x >= 1400) {
		tanks_ally[0].SetPosition(1400, 600);
		tanks_ally[0].isAppearArea = false;
	}

	if (player->GetPosition().x >= 2200) {
		isInarea = true;
		if (isAlreadyReach == false) {
			tanks_enemy[0].hp = 2000;
			isAlreadyReach = true;
		}
	}

	if (enemys.size() < 11)
	{
		soundeffect_germantalk[Random(5)].play();
		enemys.push_back(Enemy(&enemyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x + 1100, 700.f), 0));
		enemys.push_back(Enemy(&enemyTexture2, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x + 1200, 800.f), 1));
		enemys.push_back(Enemy(&enemyTexture2, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x + 1100, 900.f), 1));
	}
	if (allys.size() < 8)
	{
		soundeffect_allytalk[Random(5)].play();
		allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x - 1100, 700.f), 0));
		allys.push_back(Ally(&allyTexture, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x - 1200, 800.f), 0));
		allys.push_back(Ally(&allyTexture2, Vector2u(3, 8), 0.1f, 250.f, Vector2f(view.getCenter().x - 1100, 900.f), 1));
	}
	if (windmills[0].isComplete == true)
	{
		score += 4000;
		UpdateScore();
		gameMode = 2;
		gameMode_isInitial = false;
	}
	for (Tower& tower : towers)
	{
		tower.isStart = true;
	}
	for (Tower& tower2 : towers2)
	{
		tower2.isStart = true;
	}
	if (tanks_enemy[0].isAlive == false) {
		score += 10000;
		UpdateScore();
		gameMode = 3;
		if (isGameover == false) {
			isEnd = true;
		}
		soundeffect_cheer.play();
		gameMode_isInitial = false;
	}
}

///////////////////////////////////////////// Input Update ////////////////////////////////////////////////// 
void GameState2::UpdateInput(const float& deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && getKeyTime() && isGameover == false) { //From State.h 

		if (isPause == false) {
			battlesound.pause();
			backgroundsound.pause();
			clicksound.play();
			UpdateNameKillScore();
			pauseState();
			//PauseMenu
			pauseMenu = new PauseMenu(*window, font, view);
			pauseMenu->addButton(view.getCenter().x - window->getSize().x / 2 + 650, 600, "YES");
			pauseMenu->addButton(view.getCenter().x - window->getSize().x / 2 + 960, 600, "NO");
			battlesound.pause();
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && getKeyTime()) {
		if (dialogNum < 16 && isBegin == true) {
			dialogNum += 1;
		}
		if (isContinue == true) {
			fade->isFade = true;
			UpdateNameKillScore();
			UpdateScoreboardwithKill();
			mode = 1;
		}
		if (isContinue2 == true) {
			fade->isFade = true;
			UpdateNameKillScore();
			UpdateScoreboardwithKill();
			mode = 2;
		}

	}


}

///////////////////////////////////////// Input Player Update ////////////////////////////////////////////////// 
void GameState2::UpdatePlayerInput(const float& deltaTime)
{
	if (battlesound.getStatus() == 0) { battlesound.play(); }

	if (!(dialogNum >= 0  && dialogNum <= 15)) {
		if (player->isAlive == true && tanks_ally[0].isAlive == true) {
			player->PlayerInput();
		}
		else
		{
			player->isStop = true;
		}
	}
	else
	{
		player->isStop = true;
	}

	if (totalTimemode >= 3) {
		randommode = rand() % 2;
		totalTimemode = 0;
	}

	//Random
	for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++) {
		if (enemys[Enemy_Num].isAlive == true) {

			if (randommode == 0) {
				enemys[Enemy_Num].EnemyInput(deltaTime, player->GetPosition());	//Enemy walk -> Player
			}
			else if (randommode == 1) {

				randomSwitch = (rand() % 100) / 100.f;
				if (totalTime >= randomSwitch) {
					if (allys.size() > 0) {
						randomshoot1 = Random(allys.size());
					}
					totalTime = 0;
				}
				if (allys.size() > randomshoot1) {
					if (allys.size() > 0 && allys[randomshoot1].isAlive == true) {
						enemys[Enemy_Num].EnemyInput(deltaTime, allys[randomshoot1].GetPosition()); //Ally walk -> Enemy
					}
				}
			}
		}
		for (size_t Tank_Num = 0; Tank_Num < tanks_enemy.size(); Tank_Num++)
		{
			if (tanks_enemy[Tank_Num].isAlive == true) {
				if (allys.size() > randomshoot1) {
					if (allys.size() > 0 && allys[randomshoot1].isAlive == true) {
						tanks_enemy[Tank_Num].TankInput(deltaTime, allys[randomshoot1].GetPosition());
					}
				}
			}
		}
	}
	totalTime += deltaTime;
	totalTimemode += deltaTime;
	totalTimetutorial += deltaTime;

	for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++) {
		randomSwitch = (rand() % 100) / 100.f;
		if (allys[Ally_Num].isAlive == true) {

			if (totalTime >= randomSwitch) {
				if (enemys.size() > 0) {
					randomshoot2 = Random(enemys.size());
				}
				totalTime = 0;
			}
			if (enemys.size() > randomshoot2) {
				if (enemys.size() > 0 && enemys[randomshoot2].isAlive == true) {
					allys[Ally_Num].AllyInput(deltaTime, enemys[randomshoot2].GetPosition()); //Enemy walk -> Ally
				}
			}

		}

		for (size_t Tank_Num = 0; Tank_Num < tanks_ally.size(); Tank_Num++)
		{
			if (tanks_ally[Tank_Num].isAlive == true) {
				if (enemys.size() > randomshoot2) {
					if (enemys.size() > 0 && enemys[randomshoot2].isAlive == true) {
						tanks_ally[Tank_Num].TankInput(deltaTime, enemys[randomshoot2].GetPosition());
					}
				}
			}
		}
	}



}

///////////////////////////////////////////// Main Update ////////////////////////////////////////////////// 
void GameState2::Update(const float& deltaTime, Event evnt)
{
	UpdateKeytime(deltaTime);
	UpdateMouseAimPosition(); //Update All
	UpdateInput(deltaTime);

	if (isPause == false) //Unpause Update
	{
		if (fade->isFade == true)
		{
			fade->Update(deltaTime);
			if (fade->isFadeDone == true && mode == 0) {
				clicksound.play();
				battlesound.stop();
				backgroundsound.stop();
				endState(); //From State.h
			}
			if (fade->isFadeDone == true && mode == 1) {
				clicksound.play();
				battlesound.stop();
				backgroundsound.stop();
				endState(); //From State.h
				states->push(new ScoreboardState(window, states)); //From State.h
			}
			if (fade->isFadeDone == true && mode == 2) {
				clicksound.play();
				battlesound.stop();
				backgroundsound.stop();
				endState(); //From State.h
				states->push(new LoadingState2(window, states)); //From State.h GO TO VICTORY STATE
			}
		}
		else {

			if (fade->isBright == true) {
				fade->Update(deltaTime);
			}

			//Push back here! 
			//...
			////////////////GAME STATES/////////////

			if (gameMode == 0) {
				AllIntroduction();
			}
			else if (gameMode == 1) {
				FinalState();
				countergameMode1 += deltaTime;
			}

			if (planes_ally.size() < 1 && isAirstrike == true) {
				planes_ally.push_back(Plane(&allyplaneTexture, &bombTexture1, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 800.f, Vector2f(0.f, 200.f), 1)); //ally = 1
			}
			else if (planes_ally.size() < 1 && isAirsupport == true) {
				planes_ally.push_back(Plane(&allyplaneTexture, &bombTexture1, &fireTexture, Vector2u(1, 1), Vector2u(28, 1), Vector2u(12, 1), 0.1f, 800.f, Vector2f(0.f, 200.f), 1)); //ally = 1
			}


			//Input Update
			UpdatePlayerInput(deltaTime);
			//Camera Update
			CameraView();
			//Charactor Update
			player->Update(deltaTime, aimDir);
			for (Enemy& enemy : enemys) { enemy.Update(deltaTime); }
			for (Ally& ally : allys) { ally.Update(deltaTime); }
			for (Tank& tank_ally : tanks_ally) { tank_ally.Update(deltaTime); }
			for (Tank& tank_enemy : tanks_enemy) { tank_enemy.Update(deltaTime); }
			for (Item& firstaid : firstaids) { firstaid.Update(deltaTime); }
			for (Item& armorr : armors) { armorr.Update(deltaTime); }
			for (Item& gun : guns) { gun.Update(deltaTime); }
			for (Item& air : airsupports) { air.Update(deltaTime); }
			for (Item& heal : healtanks) { heal.Update(deltaTime); }
			for (Item& airstrike : airstrikes) { airstrike.Update(deltaTime); }
			for (Plane& plane_enemy : planes_enemy) { plane_enemy.Update(deltaTime); }
			for (Plane& plane_ally : planes_ally) { plane_ally.Update(deltaTime); }
			for (Plane& plane_ally_b : planes_ally_bg) { plane_ally_b.Update(deltaTime); }
			for (Plane& plane_enemy_b : planes_enemy_bg) { plane_enemy_b.Update(deltaTime); }
			for (BulletPlayer& bullet : bullets) { bullet.Move(deltaTime); }
			for (BulletBot& bullet_a : bullets_ally) { bullet_a.Move(deltaTime); }
			for (BulletBot& bullet_e : bullets_enemy) { bullet_e.Move(deltaTime); }
			for (Windmill& windmill : windmills) { windmill.Update(deltaTime); }
			for (Tower& tower : towers) { tower.Update(deltaTime); }
			for (Tower& tower2 : towers2) { tower2.Update(deltaTime); }
			for (Effect& bombeffect : bombeffects) { bombeffect.Update(deltaTime); }
			for (Bomb& bomb1 : bombs1) { bomb1.Update(deltaTime); }
			for (Effect& bloodeffect : bloodeffects) { bloodeffect.Update(deltaTime); }
			//Others Update
			UpdateBullet(deltaTime);
			UpdateCollision(deltaTime);
			UpdateDelete(deltaTime);
			UpdateKill(deltaTime);
			UpdateKillstreak();
			UpdateHealth();
			if ((player->isAlive == false || tanks_ally[0].isAlive == false) && isEnd == false)
			{
				isGameover = true;
				CheckGameover(deltaTime);
			}

			if (isEnd == true && isGameover == false) {
				CheckGamewin(deltaTime);
			}
			if (Airsupport > 0 || isAirstrike == true) {
				AirsupportFadeText(deltaTime);
			}
		}

	}
	else if (isPause == true) //Pause Update
	{
		pauseMenu->Update(mousePosView);
		UpdatePauseMenuButton();
	}

	if (isInitial == true) {
		isInitial = false;
	}
}

///////////////////////////////////////////// Collision  ////////////////////////////////////////////////// 
void GameState2::UpdateCollision(const float& deltaTime)
{
	//Mission


	//PlaneSound
	for (Plane& plane_ally : planes_ally)
	{
		if (view.getCenter().x - 2000 < plane_ally.GetPosition().x && plane_ally.GetPosition().x < view.getCenter().x + 2000) {
			if (soundeffect_plane1.getStatus() == 0) {
				soundeffect_plane1.play();
			}
		}
		if (view.getCenter().x - 100 < plane_ally.GetPosition().x && plane_ally.GetPosition().x < view.getCenter().x + 100 && isAirstrike == true ) {
			plane_ally.isRange = true;
			if (!(gameMode == 0) && isGameover == false && isEnd == false)
			{
				bombeffects.push_back(Effect(&ef_bomb, Vector2u(25, 2), 0.1f, 500, 1, Vector2f(2850+Random(100), plane_ally.GetPosition().y + 100), 0));
				isAlreadyBomb = true;
				isAirstrike = false;
				for (size_t i = 0; i < bombeffects.size(); i++)
				{
					bombeffects[i].isMissionbomb = true;
					bombeffects[i].randomstop = 500;
				}

			}
		}
		else if (view.getCenter().x - 100 < plane_ally.GetPosition().x && plane_ally.GetPosition().x < view.getCenter().x + 100 && Airsupport > 0 && isAirsupport == true) {
			plane_ally.isRange = true;
			if (!(gameMode == 0) && isGameover == false && isEnd == false)
			{
				int x = Random(4);
				if (x == 0) {
					firstaids.push_back(Item(&firstaidTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(300), plane_ally.GetPosition().y+100), 0));
					Airsupport--;
					isAirsupport = false;
				}
				else  if (x == 1) {
					guns.push_back(Item(&gunTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(300), plane_ally.GetPosition().y + 100), 1));
					Airsupport--;
					isAirsupport = false;
				}
				else if (x == 2) {
					armors.push_back(Item(&armorTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(300), plane_ally.GetPosition().y + 100), 0));
					Airsupport--;
					isAirsupport = false;
				}
				else if (x == 3) {
					healtanks.push_back(Item(&healtankTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(300), plane_ally.GetPosition().y + 100), 0));
					Airsupport--;
					isAirsupport = false;
				}
			}
		}
	}
	for (Plane& plane_enemy : planes_enemy)
	{
		if (view.getCenter().x - 2000 < plane_enemy.GetPosition().x && plane_enemy.GetPosition().x < view.getCenter().x + 2000) {
			plane_enemy.isRange = true;
			if (soundeffect_plane2.getStatus() == 0) {
				soundeffect_plane2.play();
			}
		}
		if (view.getCenter().x - 100 < plane_enemy.GetPosition().x && plane_enemy.GetPosition().x < view.getCenter().x + 100 && isAlreadyBomb == false) {
			if (plane_enemy.isAlive == true) {
				bombeffects.push_back(Effect(&ef_bomb, Vector2u(25, 2), 0.1f, 500, 1, Vector2f(view.getCenter().x + Random(300), plane_enemy.GetPosition().y+100), 0));
				isAlreadyBomb = true;
			}
		}
	}


	//CheckCollision for Platforms
	for (Platform& platform : platforms)
	{
		platform.GetCollision().CheckCollision(player->GetCollision(), 1.f);
		platform.GetCollision2().CheckCollision(player->GetCollision(), 1.f);
		for (int Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
		{
			platform.GetCollision().CheckCollision(enemys[Enemy_Num].GetCollision(), 1.f);
			platform.GetCollision2().CheckCollision(enemys[Enemy_Num].GetCollision(), 1.f);
		}
		for (int Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
		{
			platform.GetCollision().CheckCollision(allys[Ally_Num].GetCollision(), 1.f);
			platform.GetCollision2().CheckCollision(allys[Ally_Num].GetCollision(), 1.f);
		}

	}

	//Check Player has life
	if (player->isAlive == true) {

		for (Tank& tank_ally : tanks_ally)
		{
			if (tank_ally.isAlive == true)
			{
				if (player->GetGlobalbounce().intersects(tank_ally.GetGlobalbounceisRange())) {
					tank_ally.isRange = true;
					if (soundeffect_tankmove.getStatus() == 0)
					{
						soundeffect_tankmove.play();
					}
					isAlreadyMoveTank = true;
				}
			}
		}
		//CheckCollision Player collect -> FirstAid
		for (size_t First_Num = 0; First_Num < firstaids.size(); First_Num++) {
			if (firstaids[First_Num].isStop == true) {
				if (player->GetCollision().CheckCollision(firstaids[First_Num].GetCollision(), 0.f))
				{
					if (firstaids[First_Num].isCollect == false && player->hp < 1000) {
						player->hp += 500;
						isAlreadyCollect++;
						firstaids[First_Num].isCollect = true;
						soundeffect_collectfirst.play();
					}
				}
			}
		}
		//CheckCollision Player collect -> Armor
		for (size_t Armor_Num = 0; Armor_Num < armors.size(); Armor_Num++) {
			if (armors[Armor_Num].isStop == true) {
				if (player->GetCollision().CheckCollision(armors[Armor_Num].GetCollision(), 0.f))
				{
					if (armors[Armor_Num].isCollect == false && player->armor < 1000) {
						player->armor += 350;
						armors[Armor_Num].isCollect = true;
						isAlreadyCollect++;
						soundeffect_collectfirst.play();
					}
				}
			}
		}
		//CheckCollision Player collect -> healtank
		for (size_t Heal_Num = 0; Heal_Num < healtanks.size(); Heal_Num++) {
			if (healtanks[Heal_Num].isStop == true) {
				if (player->GetCollision().CheckCollision(healtanks[Heal_Num].GetCollision(), 0.f))
				{
					if (healtanks[Heal_Num].isCollect == false && player->armor < 1000) {
						tanks_ally[0].hp += 150;
						healtanks[Heal_Num].isCollect = true;
						soundeffect_collectfirst.play();
					}
				}
			}
		}
		//CheckCollision Player collect -> New Gun
		for (size_t Gun_Num = 0; Gun_Num < guns.size(); Gun_Num++) {
			if (guns[Gun_Num].isStop == true) {
				if (player->GetCollision().CheckCollision(guns[Gun_Num].GetCollision(), 0.f))
				{
					if (guns[Gun_Num].isCollect == false) {
						player->isNewgun = true;
						player->totalTime = 0.f;
						guns[Gun_Num].isCollect = true;
						soundeffect_collectgun.play();
					}
				}
			}
		}
		//CheckCollision Player collect -> AirSupport
		for (size_t Air_Num = 0; Air_Num < airsupports.size(); Air_Num++) {
			if (player->GetCollision().CheckCollision(airsupports[Air_Num].GetCollision(), 0.f))
			{
				if (airsupports[Air_Num].isCollect == false) {
					airsupports[Air_Num].isCollect = true;
					Airsupport++;
					isAirsupport = true;
					soundeffect_collectgun.play();
				}
			}
		}
		//CheckCollision Player collect -> AirStrike
		for (size_t Air_Num = 0; Air_Num < airstrikes.size(); Air_Num++) {
			if (player->GetCollision().CheckCollision(airstrikes[Air_Num].GetCollision(), 0.f))
			{
				if (airstrikes[Air_Num].isCollect == false) {
					airstrikes[Air_Num].isCollect = true;
					isAirstrike = true;
					soundeffect_collectgun.play();
				}
			}
		}
		//CheckCollision bulletEnemy shoot -> Player
		for (size_t Bullet_Num = 0; Bullet_Num < bullets_enemy.size(); Bullet_Num++) {
			if (player->GetCollision().CheckCollision(bullets_enemy[Bullet_Num].GetCollision(), 1.f))
			{
				if (player->armor <= 0) {
					player->hp -= 50;
				}
				else
				{
					player->armor -= 50;
				}

				player->isDamage = true;

				bullets_enemy[Bullet_Num].SetDeletePosition();

				if (player->hp <= 0)
				{
					player->isAlive = false;
					soundeffect_dead[Random(4)].play();
				}
			}
		}
	}

	//Check All Enemy
	for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
	{
		//Check Enemy has life
		if (enemys[Enemy_Num].isAlive == true)
		{
			//Check Player has life
			if (player->isAlive == true)
			{
				//CheckCollision Player & Enemy
				if (enemys[Enemy_Num].GetCollision().CheckCollision(player->GetCollision(), 0.8f))
				{
					player->hp -= 1;
					player->isDamage = true;
					enemys[Enemy_Num].hp -= 1;
					enemys[Enemy_Num].isDamage = true;

					if (player->hp <= 0)
					{
						player->isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
					if (enemys[Enemy_Num].hp <= 0)
					{
						enemys[Enemy_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}
			}

			//CheckCollision bulletPlayer shoot -> Enemy
			for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
			{
				if (enemys[Enemy_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f))
				{
					if (enemys[Enemy_Num].armor > 0) {
						enemys[Enemy_Num].armor -= 30;
					}
					else
					{
						enemys[Enemy_Num].hp -= 30;
					}

					enemys[Enemy_Num].isDamage = true;
					score += 50;
					UpdateScore();

					bullets[Bullet_Num].SetDeletePosition();

					if (enemys[Enemy_Num].hp <= 0)
					{
						kill++;
						enemys[Enemy_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
						score += 200;
						UpdateScore();
						int x = rand() % randomNum;
						if (x == 0) {
							airsupports.push_back(Item(&airsupportTexture, Vector2u(1, 1), 0.5f, 100, Vector2f(enemys[Enemy_Num].GetPosition()), 2));
							randomNum = 10;
						}
						else if (x >= 1 && x <= 3) {
							airstrikes.push_back(Item(&airstrikeTexture, Vector2u(1, 1), 0.5f, 100, Vector2f(enemys[Enemy_Num].GetPosition()), 3));
							randomNum = 10;
						}
						else
						{
							randomNum--;
							if (randomNum < 2) randomNum = 2;
						}
					}

				}
			}

			//CheckCollision bulletAlly shoot -> Enemy
			for (size_t Bullet_Num = 0; Bullet_Num < bullets_ally.size(); Bullet_Num++)
			{
				if (enemys[Enemy_Num].GetCollision().CheckCollision(bullets_ally[Bullet_Num].GetCollision(), 1.f))
				{
					if (enemys[Enemy_Num].armor > 0) {
						enemys[Enemy_Num].armor -= 30;
					}
					else
					{
						enemys[Enemy_Num].hp -= 30;
					}
					enemys[Enemy_Num].isDamage = true;

					bullets_ally[Bullet_Num].SetDeletePosition();

					if (enemys[Enemy_Num].hp <= 0)
					{
						enemys[Enemy_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}

				}
			}
			//CheckCollision Ally & Enemy
			for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
			{
				if (allys[Ally_Num].isAlive == true) {
					if (enemys[Enemy_Num].GetCollision().CheckCollision(allys[Ally_Num].GetCollision(), 0.8f))
					{
						allys[Ally_Num].hp -= 1;
						allys[Ally_Num].isDamage = true;
						enemys[Enemy_Num].hp -= 1;
						enemys[Enemy_Num].isDamage = true;

						if (allys[Ally_Num].hp <= 0)
						{
							allys[Ally_Num].isAlive = false;
							soundeffect_dead[Random(4)].play();
						}
						if (enemys[Enemy_Num].hp <= 0)
						{
							enemys[Enemy_Num].isAlive = false;
							soundeffect_dead[Random(4)].play();
						}
					}
				}
			}
		}
	}

	//CheckCollision bulletEnemy shoot -> Ally
	for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
	{
		//Check Ally has life
		if (allys[Ally_Num].isAlive == true) {
			for (size_t Bullet_Num = 0; Bullet_Num < bullets_enemy.size(); Bullet_Num++) {
				if (allys[Ally_Num].GetCollision().CheckCollision(bullets_enemy[Bullet_Num].GetCollision(), 1.f))
				{
					if (allys[Ally_Num].armor > 0) {
						allys[Ally_Num].armor -= 60;
					}
					else
					{
						allys[Ally_Num].hp -= 30;
					}
					allys[Ally_Num].isDamage = true;

					bullets_enemy.erase(bullets_enemy.begin() + Bullet_Num);
					if (allys[Ally_Num].hp <= 0)
					{
						allys[Ally_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}
			}
		}
	}

	//Check All Exposion AOE
	for (size_t Bomb_Num = 0; Bomb_Num < bombeffects.size(); Bomb_Num++)
	{
		//Check Player has life
		if (player->isAlive == true) {
			//CheckCollision Player & Exposion
			if (player->GetGlobalbounce().intersects(bombeffects[Bomb_Num].GetGlobalbounce()))
			{
				if (bombeffects[Bomb_Num].isBomb == true) {
					//Solve about hit first sec and not hit anymore...
					if (player->armor <= 0) {
						player->hp -= 100;
					}
					else
					{
						player->armor -= 100;
					}
					player->isDamage = true;
				}
				if (player->hp <= 0)
				{
					player->isAlive = false;

				}
			}
		}

		//Check All Enemy
		for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
		{
			//Check Enemy has life
			if (enemys[Enemy_Num].isAlive == true)
			{
				//CheckCollision Enemy & Exposion
				if (enemys[Enemy_Num].GetGlobalbounce().intersects(bombeffects[Bomb_Num].GetGlobalbounce()))
				{
					if (bombeffects[Bomb_Num].isBomb == true) {
						if (enemys[Enemy_Num].armor > 0) {
							enemys[Enemy_Num].armor -= 0;
						}
						else
						{
							enemys[Enemy_Num].hp -= 60;
						}
						enemys[Enemy_Num].isDamage = true;
					}
					if (enemys[Enemy_Num].hp <= 0)
					{
						enemys[Enemy_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}
			}
		}

		//Check All Ally
		for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
		{
			//Check Ally has life
			if (allys[Ally_Num].isAlive == true)
			{
				//CheckCollision Ally & Exposion
				if (allys[Ally_Num].GetGlobalbounce().intersects(bombeffects[Bomb_Num].GetGlobalbounce()))
				{
					if (bombeffects[Bomb_Num].isBomb == true) {
						if (allys[Ally_Num].armor > 0) {
							allys[Ally_Num].armor -= 60;
						}
						else
						{
							allys[Ally_Num].hp -= 60;
						}
						allys[Ally_Num].isDamage = true;
					}
					if (allys[Ally_Num].hp <= 0)
					{
						allys[Ally_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}

			}
		}

		//Check All EnemyTank
		for (size_t Tank_Num = 0; Tank_Num < tanks_enemy.size(); Tank_Num++)
		{
			//Check Tank has life
			if (tanks_enemy[Tank_Num].isAlive == true)
			{
				//CheckCollision Tanks & Bomb
				if (tanks_enemy[Tank_Num].GetGlobalbounce().intersects(bombeffects[Bomb_Num].GetGlobalbounce()))
				{
					if (bombeffects[Bomb_Num].isBomb == true) {
						tanks_enemy[Tank_Num].hp -= 200;
						tanks_enemy[Tank_Num].isDamage = true;
					}
					if (tanks_enemy[Tank_Num].hp <= 0)
					{
						tanks_enemy[Tank_Num].isAlive = false;
						soundeffect_tankexposion.play();
					}
				}
			}
		}
		if (bombeffects[Bomb_Num].isBomb == true) {
			soundeffect_planebomb[Random(3)].play();
		}
	}

	//Check All Bomb AOE
	for (size_t Bomb_Num = 0; Bomb_Num < bombs1.size(); Bomb_Num++)
	{
		//Check Player has life
		if (player->isAlive == true) {
			//CheckCollision Player & Exposion
			if (player->GetGlobalbounce().intersects(bombs1[Bomb_Num].GetGlobalbounce()))
			{
				if (bombs1[Bomb_Num].isBoom == true) {
					if (player->armor <= 0) {
						player->hp -= 100;
					}
					else
					{
						player->armor -= 100;
					}
					player->isDamage = true;
				}
				if (player->hp <= 0)
				{
					player->isAlive = false;
					soundeffect_dead[Random(4)].play();
				}
			}
		}

		//Check All Enemy
		for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
		{
			//Check Enemy has life
			if (enemys[Enemy_Num].isAlive == true)
			{
				//CheckCollision Enemy & Exposion
				if (enemys[Enemy_Num].GetGlobalbounce().intersects(bombs1[Bomb_Num].GetGlobalbounce()))
				{
					if (bombs1[Bomb_Num].isBoom == true) {
						if (enemys[Enemy_Num].armor > 0) {
							enemys[Enemy_Num].armor -= 60;
						}
						else
						{
							enemys[Enemy_Num].hp -= 60;
						}
						enemys[Enemy_Num].isDamage = true;
					}
					if (enemys[Enemy_Num].hp <= 0)
					{
						kill++;
						enemys[Enemy_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}
			}
		}

		//Check All Ally
		for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
		{
			//Check Ally has life
			if (allys[Ally_Num].isAlive == true)
			{
				//CheckCollision Ally & Exposion
				if (allys[Ally_Num].GetGlobalbounce().intersects(bombs1[Bomb_Num].GetGlobalbounce()))
				{
					if (bombs1[Bomb_Num].isBoom == true) {
						if (allys[Ally_Num].armor > 0) {
							allys[Ally_Num].armor -= 60;
						}
						else
						{
							allys[Ally_Num].hp -= 60;
						}
						allys[Ally_Num].isDamage = true;
					}
					if (allys[Ally_Num].hp <= 0)
					{
						allys[Ally_Num].isAlive = false;
						soundeffect_dead[Random(4)].play();
					}
				}

			}
		}

		//Check All Tank
		for (size_t Tank_Num = 0; Tank_Num < tanks_ally.size(); Tank_Num++)
		{
			//Check Tank has life
			if (tanks_ally[Tank_Num].isAlive == true)
			{
				//CheckCollision Tanks & Bomb
				if (tanks_ally[Tank_Num].GetGlobalbounce().intersects(bombs1[Bomb_Num].GetGlobalbounce()))
				{
					if (bombs1[Bomb_Num].isBoom == true) {
						tanks_ally[Tank_Num].hp -= 100;
						tanks_ally[Tank_Num].isDamage = true;
					}
					if (tanks_ally[Tank_Num].hp <= 0)
					{
						tanks_ally[Tank_Num].isAlive = false;
					}
				}
			}
		}

		//Check Bomb with Bomb
		for (size_t Bomb_Num2 = 0; Bomb_Num2 < bombs1.size(); Bomb_Num2++)
		{
			if (bombs1[Bomb_Num2].GetGlobalbounce().intersects(bombs1[Bomb_Num].GetGlobalbounce()))
			{
				if (bombs1[Bomb_Num2].isBoom == true || bombs1[Bomb_Num].isBoom == true) {
					bombs1[Bomb_Num2].isBoom = true;
					bombs1[Bomb_Num].isBoom = true;
				}
			}
		}

		for (size_t Tower_Num = 0; Tower_Num < towers.size(); Tower_Num++)
		{
			if (bombs1[Bomb_Num].GetGlobalbounce().intersects(towers[Tower_Num].GetGlobalbounce()))
			{
				if (bombs1[Bomb_Num].isBoom == true) {
					towers[Tower_Num].hp -= 200;  // -5
					towers[Tower_Num].isDamage = true;

					score += 100;
					UpdateScore();
					;
					if (towers[Tower_Num].hp <= 0)
					{
						score += 2000;
						UpdateScore();
						towers[Tower_Num].isAlive = false;
					}
				}
			}
		}
		for (size_t Tower_Num = 0; Tower_Num < towers2.size(); Tower_Num++)
		{
			if (bombs1[Bomb_Num].GetGlobalbounce().intersects(towers2[Tower_Num].GetGlobalbounce()))
			{
				if (bombs1[Bomb_Num].isBoom == true) {
					towers2[Tower_Num].hp -= 200;  // -5
					towers2[Tower_Num].isDamage = true;

					score += 100;
					UpdateScore();

					if (towers2[Tower_Num].hp <= 0)
					{
						score += 2000;
						UpdateScore();
						towers2[Tower_Num].isAlive = false;
					}
				}
			}
		}

		if (bombs1[Bomb_Num].isBoom == true)
		{
			soundeffect_bomb.play();
		}
		if (bombs1[Bomb_Num].isHit == true && bombs1[Bomb_Num].isAlreadyBoom == false)
		{
			if (soundeffect_ticking.getStatus() == 0) { soundeffect_ticking.play(); }
		}
	}

	//Check All Ally Tanks
	for (size_t Tank_Num = 0; Tank_Num < tanks_ally.size(); Tank_Num++)
	{
		//Check Tank has life
		if (tanks_ally[Tank_Num].isAlive == true)
		{
			//Check Collision Tank -> Winmill
			for (Windmill& windmill : windmills)
			{
				if (player->isAlive == true) {
					if (tanks_ally[Tank_Num].GetGlobalbounce().intersects(windmill.GetGlobalbounce())
						&& player->GetGlobalbounce().intersects(windmill.GetGlobalbounce())) {
						windmill.isActiveAlly = true;
					}
				}
			}
			//Check Collision Enemy Bullet shoot -> tank
			for (size_t Bullet_Num = 0; Bullet_Num < bullets_enemy.size(); Bullet_Num++)
			{
				if (tanks_ally[Tank_Num].GetCollision().CheckCollision(bullets_enemy[Bullet_Num].GetCollision(), 1.f))
				{
					tanks_ally[Tank_Num].hp -= 1;  // -5
					tanks_ally[Tank_Num].isDamage = true;
					soundeffect_tankbullethit.play();

					bullets_enemy.erase(bullets_enemy.begin() + Bullet_Num);
					if (tanks_ally[Tank_Num].hp <= 0)
					{
						tanks_ally[Tank_Num].isAlive = false;
					}
				}

			}

		}
		else
		{
			if (soundeffect_tankexposion.getStatus() == 0) {
				soundeffect_tankexposion.play();
			}
		}
	}
	//Check All Enemy Tanks
	for (size_t Tank_Num = 0; Tank_Num < tanks_enemy.size(); Tank_Num++)
	{
		//Check Tank has life
		if (tanks_enemy[Tank_Num].isAlive == true)
		{
			//Check Collision Ally Bullet shoot -> tank
			for (size_t Bullet_Num = 0; Bullet_Num < bullets_ally.size(); Bullet_Num++)
			{
				if (tanks_enemy[Tank_Num].GetCollision().CheckCollision(bullets_ally[Bullet_Num].GetCollision(), 1.f))
				{
					tanks_enemy[Tank_Num].hp -= 1;
					tanks_enemy[Tank_Num].isDamage = true;
					soundeffect_tankbullethit.play();
					bullets_ally.erase(bullets_ally.begin() + Bullet_Num);
				}
			}
		}
		else
		{
			if (soundeffect_tankexposion.getStatus() == 0 && isAlreadyplay2 == false) {
				soundeffect_tankexposion.play();
				isAlreadyplay2 = true;
			}
		}
	}
	//Check All Enemy Tanks
	for (size_t Tank_Num = 0; Tank_Num < tanks_enemy.size(); Tank_Num++)
	{
		//Check Tank has life
		if (tanks_enemy[Tank_Num].isAlive == true)
		{
			//Check Collision Player Bullet shoot -> tank
			for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
			{
				if (tanks_enemy[Tank_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f))
				{
					tanks_enemy[Tank_Num].hp -= 1;
					score += 200;
					UpdateScore();
					tanks_enemy[Tank_Num].isDamage = true;
					soundeffect_tankbullethit.play();
					bullets.erase(bullets.begin() + Bullet_Num);
				}
			}
		}
		else
		{
			if (soundeffect_tankexposion.getStatus() == 0 && isAlreadyplay2 == false) {
				soundeffect_tankexposion.play();
				isAlreadyplay2 = true;
			}
		}
	}

	//Check All Collision Towers
	for (size_t Tower_Num = 0; Tower_Num < towers.size(); Tower_Num++)
	{
		//Check Tower has live
		if (towers[Tower_Num].isAlive == true) {
			for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
			{
				if (towers[Tower_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f))
				{
					towers[Tower_Num].hp -= 30;  // -5
					towers[Tower_Num].isDamage = true;

					score += 100;
					UpdateScore();

					bullets.erase(bullets.begin() + Bullet_Num);
					if (towers[Tower_Num].hp <= 0)
					{
						score += 2000;
						UpdateScore();
						towers[Tower_Num].isAlive = false;
					}
				}
			}

		}
		else
		{
			if (towers[Tower_Num].isAlreadyBoom == false) {
				soundeffect_tankexposion.play();
				towers[Tower_Num].isAlreadyBoom = true;
			}
		}
	}

	//Check All Collision Towers2
	for (size_t Tower_Num = 0; Tower_Num < towers2.size(); Tower_Num++)
	{
		//Check Tower has live
		if (towers2[Tower_Num].isAlive == true) {
			for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
			{
				if (towers2[Tower_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f))
				{
					towers2[Tower_Num].hp -= 30;  // -5
					towers2[Tower_Num].isDamage = true;

					score += 100;
					UpdateScore();

					bullets.erase(bullets.begin() + Bullet_Num);
					if (towers2[Tower_Num].hp <= 0)
					{
						score += 2000;
						UpdateScore();
						towers2[Tower_Num].isAlive = false;
					}
				}
			}

		}
		else
		{
			if (towers2[Tower_Num].isAlreadyBoom == false) {
				soundeffect_tankexposion.play();
				towers2[Tower_Num].isAlreadyBoom = true;
			}
		}
	}

	//CheckCollision bulletPlayer shoot -> Bomb
	for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
	{
		for (size_t Bomb_Num = 0; Bomb_Num < bombs1.size(); Bomb_Num++)
		{
			if (bombs1[Bomb_Num].isAlreadyBoom == false) {
				if (bombs1[Bomb_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f))
				{
					bullets[Bullet_Num].SetDeletePosition();
					bombs1[Bomb_Num].isHit = true;
				}
			}
		}
	}

	for (size_t Plane_Num = 0; Plane_Num < planes_enemy.size(); Plane_Num++)
	{
		for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
		{
			if (planes_enemy[Plane_Num].isAlive == true) {
				if (planes_enemy[Plane_Num].GetCollision().CheckCollision(bullets[Bullet_Num].GetCollision(), 1.f)) {
					bullets[Bullet_Num].SetDeletePosition();
					planes_enemy[Plane_Num].hp -= 100;
					planes_enemy[Plane_Num].isDamage = true;
					soundeffect_tankbullethit.play();
					if (planes_enemy[Plane_Num].hp <= 0) {
						planes_enemy[Plane_Num].velocity.y = 100;
						planes_enemy[Plane_Num].isAlive = false;
						score += 500;
						UpdateScore();
						soundeffect_tankexposion.play();
						int x = Random(4);
						if (x == 0) {
							firstaids.push_back(Item(&firstaidTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(100), planes_enemy[Plane_Num].GetPosition().y+100), 0));
							Airsupport--;
							isAirsupport = false;
						}
						else  if (x == 1) {
							guns.push_back(Item(&gunTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(100), planes_enemy[Plane_Num].GetPosition().y + 100), 1));
							Airsupport--;
							isAirsupport = false;
						}
						else if (x == 2) {
							armors.push_back(Item(&armorTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(100), planes_enemy[Plane_Num].GetPosition().y + 100), 0));
							Airsupport--;
							isAirsupport = false;
						}
						else if (x == 3) {
							healtanks.push_back(Item(&healtankTexture, Vector2u(3, 4), 0.5f, 100, Vector2f(view.getCenter().x + Random(100), planes_enemy[Plane_Num].GetPosition().y + 100), 0));
							Airsupport--;
							isAirsupport = false;
						}
					}
				}
			}
		}
	}

}

//////////////////////////////////////////// Update Bullet  ///////////////////////////////////////////////// 
void GameState2::UpdateBullet(const float& deltaTime)
{
	if (player->isPush == true) {
		bullets.push_back(BulletPlayer(&bulletTexture, player->GetPosition(), aimDirNorm, aimDir, player->GetfaceRight())); // Vector bullets
	}

	for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
	{
		if (enemys[Enemy_Num].isAlive == true) {
			if (enemys[Enemy_Num].isPush == true) {
				soundeffect_shoot.play();
				if (allys.size() > 0) {
					int randomshoot = rand() % allys.size();
					int randommode = rand() % 2;
					if (randommode == 0) {
						bullets_enemy.push_back(BulletBot(&bulletTexture, enemys[Enemy_Num].GetPosition(), player->GetPosition(), enemys[Enemy_Num].GetfaceRight(), 0)); // Vector bullets
					}
					else if (randommode == 1) {
						bullets_enemy.push_back(BulletBot(&bulletTexture, enemys[Enemy_Num].GetPosition(), allys[randomshoot].GetPosition(), enemys[Enemy_Num].GetfaceRight(), 0)); // Vector bullets
					}
				}
			}
		}
	}
	for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
	{
		if (allys[Ally_Num].isAlive == true) {
			if (allys[Ally_Num].isPush == true) {
				if (enemys.size() > randomshoot2) {
					if (enemys[randomshoot2].isAlive == true) {
						soundeffect_shoot.play();
						bullets_ally.push_back(BulletBot(&bulletTexture, allys[Ally_Num].GetPosition(), enemys[randomshoot2].GetPosition(), allys[Ally_Num].GetfaceRight(), 1)); // Vector bullets
					}
				}
			}
		}
	}

	for (size_t Tank_Num = 0; Tank_Num < tanks_ally.size(); Tank_Num++)
	{
		if (tanks_ally[Tank_Num].isAlive == true) {
			if (tanks_ally[Tank_Num].isPush == true) {
				if (enemys.size() > randomshoot2) {
					if (enemys[randomshoot2].isAlive == true) {
						soundeffect_tankgun.play();
						bullets_ally.push_back(BulletBot(&bulletTexture, Vector2f(tanks_ally[Tank_Num].GetPosition().x, tanks_ally[Tank_Num].GetPosition().y - 20), enemys[randomshoot2].GetPosition(), 1, 3)); // Vector bullets
					}
				}
			}
		}
	}

	for (size_t Tank_Num = 0; Tank_Num < tanks_enemy.size(); Tank_Num++)
	{
		if (tanks_enemy[Tank_Num].isAlive == true) {
			if (tanks_enemy[Tank_Num].isPush == true) {
				if (allys.size() > randomshoot1) {
					if (allys[randomshoot1].isAlive == true) {
						soundeffect_tankgun.play();
						bullets_enemy.push_back(BulletBot(&bulletTexture, Vector2f(tanks_enemy[Tank_Num].GetPosition().x, tanks_enemy[Tank_Num].GetPosition().y - 20), allys[randomshoot1].GetPosition(), 1, 2)); // Vector bullets
					}
				}
			}
		}
	}

}

void GameState2::UpdateDelete(const float& deltaTime)
{
	/////   Check if Out side of window --- > Erase it  ///////

	//All Player
		//Enemys
	for (size_t Enemy_Num = 0; Enemy_Num < enemys.size(); Enemy_Num++)
	{
		if (enemys[Enemy_Num].GetPosition().y > 3000)
		{
			if (enemys.size() == 1) { allys.clear(); }
			else { enemys.erase(enemys.begin() + Enemy_Num); }
		}

	}
	//Allys
	for (size_t Ally_Num = 0; Ally_Num < allys.size(); Ally_Num++)
	{
		if (allys[Ally_Num].GetPosition().y > 3000)
		{
			if (allys.size() == 1) { allys.clear(); }
			else { allys.erase(allys.begin() + Ally_Num); }
		}
	}
	//All Bullets
		//Player Bullets
	for (size_t Bullet_Num = 0; Bullet_Num < bullets.size(); Bullet_Num++)
	{
		if (bullets[Bullet_Num].GetPosition().y > 3000)
		{
			if (bullets.size() == 1) { bullets.clear(); }
			else { bullets.erase(bullets.begin() + Bullet_Num); }
			break;
		}
	}
	//Enemy Bullets
	for (size_t Bullet_Num = 0; Bullet_Num < bullets_enemy.size(); Bullet_Num++)
	{
		if (bullets_enemy[Bullet_Num].GetPosition().y > 3000)
		{
			if (bullets_enemy.size() == 1) { bullets_enemy.clear(); }
			else { bullets_enemy.erase(bullets_enemy.begin() + Bullet_Num); }
			break;
		}
	}
	//Ally Bullets
	for (size_t Bullet_Num = 0; Bullet_Num < bullets_ally.size(); Bullet_Num++)
	{
		if (bullets_ally[Bullet_Num].GetPosition().y > 3000)
		{
			if (bullets_ally.size() == 1) { bullets_ally.clear(); }
			else { bullets_ally.erase(bullets_ally.begin() + Bullet_Num); }
			break;
		}
	}
	//All Items
		//First aids
	for (size_t First_Num = 0; First_Num < firstaids.size(); First_Num++)
	{
		if (firstaids[First_Num].GetPosition().y > 3000)
		{
			if (firstaids.size() == 1) { firstaids.clear(); }
			else { firstaids.erase(firstaids.begin() + First_Num); }
		}
	}
	for (size_t Armor_Num = 0; Armor_Num < armors.size(); Armor_Num++)
	{
		if (armors[Armor_Num].GetPosition().y > 3000)
		{
			if (armors.size() == 1) { armors.clear(); }
			else { armors.erase(armors.begin() + Armor_Num); }
		}
	}
	for (size_t Heal_Num = 0; Heal_Num < healtanks.size(); Heal_Num++)
	{
		if (healtanks[Heal_Num].GetPosition().y > 3000)
		{
			if (healtanks.size() == 1) { healtanks.clear(); }
			else { healtanks.erase(healtanks.begin() + Heal_Num); }
		}
	}
	//Guns
	for (size_t Gun_Num = 0; Gun_Num < guns.size(); Gun_Num++)
	{
		if (guns[Gun_Num].GetPosition().y > 3000)
		{
			if (guns.size() == 1) { guns.clear(); }
			else { guns.erase(guns.begin() + Gun_Num); }
		}
	}
	for (size_t Air_Num = 0; Air_Num < airsupports.size(); Air_Num++)
	{
		if (airsupports[Air_Num].GetPosition().y > 3000)
		{
			if (airsupports.size() == 1) { airsupports.clear(); }
			else { airsupports.erase(airsupports.begin() + Air_Num); }
		}
	}
	for (size_t Air_Num = 0; Air_Num < airstrikes.size(); Air_Num++)
	{
		if (airstrikes[Air_Num].GetPosition().y > 3000)
		{
			if (airstrikes.size() == 1) { airstrikes.clear(); }
			else { airstrikes.erase(airstrikes.begin() + Air_Num); }
		}
	}
	//All Effects
		//Bombs
	for (size_t Bomb_Num = 0; Bomb_Num < bombeffects.size(); Bomb_Num++)
	{
		if (bombeffects[Bomb_Num].GetPosition().y > 3000)
		{
			if (bombeffects.size() == 1) { bombeffects.clear(); }
			else { bombeffects.erase(bombeffects.begin() + Bomb_Num); }
		}
	}
	for (size_t Bomb_Num = 0; Bomb_Num < bombs1.size(); Bomb_Num++)
	{
		if (bombs1[Bomb_Num].GetPosition().y > 3000)
		{
			if (bombs1.size() == 1) { bombs1.clear(); }
			else { bombs1.erase(bombs1.begin() + Bomb_Num); }
		}
	}
	//All Planes
	for (size_t Plane_Num = 0; Plane_Num < planes_ally.size(); Plane_Num++)
	{
		if (planes_ally[Plane_Num].GetPosition().y > 3000)
		{
			if (planes_ally.size() == 1) { planes_ally.clear(); }
			else { planes_ally.erase(planes_ally.begin() + Plane_Num); }
		}
	}
	for (size_t Plane_Num = 0; Plane_Num < planes_enemy.size(); Plane_Num++)
	{
		if (planes_enemy[Plane_Num].GetPosition().y > 500 ) {
			if (planes_enemy[Plane_Num].isAlive == false && planes_enemy[Plane_Num].isAlreadyplay == false) {
				soundeffect_bomb.play();
				planes_enemy[Plane_Num].isAlreadyplay = true;
			}
		}
		if (planes_enemy[Plane_Num].GetPosition().y > 3000)
		{
			isAlreadyBomb = false;
			if (planes_enemy.size() == 1) { planes_enemy.clear(); }
			else { planes_enemy.erase(planes_enemy.begin() + Plane_Num); }
		}
	}
}

//////////////////////////////////////////// Update Mouse Position ////////////////////////////////////////////////// 
void GameState2::UpdateMouseAimPosition()
{
	UpdateMousePositions();	//From State.h
	aimDir = mousePosView - player->GetPosition();
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
}

void GameState2::UpdateHealth()
{
	tankname.setString("A7V Enemy Tank " + to_string(tanks_enemy[0].hp) + "/2000");
	tankname.setOrigin(tankname.getGlobalBounds().width / 2, tankname.getGlobalBounds().height / 2);
}

void GameState2::CameraView()
{
	if (gameMode == 0) {
		if (player->GetPosition().x <= 800) { view1 = false; }
		else if (player->GetPosition().x > 800 && player->GetPosition().x <= 3000) { view1 = true; }
		else if (player->GetPosition().x > 2000) { view1 = false; }
	}
	else if (gameMode == 1) {
		if (player->GetPosition().x < calibrate) { view2 = false; }
		else if (player->GetPosition().x > calibrate) { calibrate = tanks_ally[0].GetPosition().x; view2 = true; }
		if (player->GetPosition().x < 3000) { view3 = true; }
		else { view3 = false; }
	}

	if ((view1 == true && gameMode == 0) || (view2 == true && view3 == true && (gameMode == 1 || gameMode == 2)) && isInarea == false)
	{
		backgroundSky.setPosition(view.getCenter().x, view.getCenter().y - 253);
		//backgroundTree1.setPosition(view.getCenter().x, view.getCenter().y + 70);
		backgroundTree2.setPosition(view.getCenter().x, view.getCenter().y + 70);
		backgroundTree3.setPosition(view.getCenter().x, view.getCenter().y + 70);
		backgroundTree4.setPosition(view.getCenter().x, view.getCenter().y + 70);
		backgroundFloor.setPosition(view.getCenter().x, view.getCenter().y + 287);


		view.setCenter(Vector2f(player->GetPosition().x, window->getSize().y / 2));
		backgroundFloor.setTextureRect(IntRect(view.getCenter().x * 1, 0, 6400, 206));
		backgroundTree1.setTextureRect(IntRect(view.getCenter().x * 1, 0, 6400, 250));
		backgroundTree2.setTextureRect(IntRect(view.getCenter().x * 0.6, 0, 6400, 250));
		backgroundTree3.setTextureRect(IntRect(view.getCenter().x * 0.5, 0, 6400, 250));
		backgroundTree4.setTextureRect(IntRect(view.getCenter().x * 0.4, 0, 6400, 250));
		backgroundSky.setTextureRect(IntRect(view.getCenter().x * 0.3, 0, 6400, 214));
	}

}

////////////////////////////////////////////  Render  ////////////////////////////////////////////////// 
void GameState2::Render(RenderTarget* target)
{
	if (!target) target = window;

	//Set Screen 
	target->setView(view);

	target->draw(backgroundSky);
	for (Plane& plane_ally_b : planes_ally_bg) { plane_ally_b.Draw(*target); }
	for (Plane& plane_enemy_b : planes_enemy_bg) { plane_enemy_b.Draw(*target); }
	target->draw(backgroundTree4);
	target->draw(backgroundTree3);
	target->draw(backgroundTree2);
	target->draw(backgroundTree1);
	target->draw(backgroundFloor);
	for (Windmill& windmill : windmills) { windmill.Draw(*target); }




	for (Platform& platform : platforms)
	{
		platform.Draw(*target);
	}


	//Sort Swap Enemys
	for (size_t i = 0; i < enemys.size(); i++)
	{
		for (size_t j = i; j < enemys.size(); j++)
		{
			if (enemys[i].GetPosition().y > enemys[j].GetPosition().y) {
				swap(enemys[i], enemys[j]);
			}
		}
	}
	//Sort Swap Allys
	for (size_t i = 0; i < allys.size(); i++)
	{
		for (size_t j = i; j < allys.size(); j++)
		{
			if (allys[i].GetPosition().y > allys[j].GetPosition().y) {
				swap(allys[i], allys[j]);
			}
		}
	}
	for (Plane& plane_enemy : planes_enemy) { plane_enemy.Draw(*target); }
	for (Plane& plane_ally : planes_ally) { plane_ally.Draw(*target); }
	for (Tower& tower : towers) { tower.Draw(*target); }
	for (Tank& tank_ally : tanks_ally) { tank_ally.Draw(*target); }
	for (Tank& tank_enemy : tanks_enemy) { tank_enemy.Draw(*target); }
	for (Item& firstaid : firstaids) { firstaid.Draw(*target); }
	for (Item& armorr : armors) { armorr.Draw(*target); }
	for (Item& gun : guns) { gun.Draw(*target); }
	for (Item& air : airsupports) { air.Draw(*target); }
	for (Item& heal : healtanks) { heal.Draw(*target); }
	for (Item& airstrike : airstrikes) { airstrike.Draw(*target); }
	for (Bomb& bomb1 : bombs1) { bomb1.Draw(*target); }
	player->Draw(*target);
	for (Enemy& enemy : enemys) { enemy.Draw(*target); }
	for (Ally& ally : allys) { ally.Draw(*target); }
	for (Effect& bombeffect : bombeffects) { bombeffect.Draw(*target); }
	for (Effect& bloodeffect : bloodeffects) { bloodeffect.Draw(*target); }
	for (Tower& tower2 : towers2) { tower2.Draw(*target); }
	for (BulletPlayer& bullet : bullets) { bullet.Draw(*target); }
	for (BulletBot& bullet_e : bullets_enemy) { bullet_e.Draw(*target); }
	for (BulletBot& bullet_a : bullets_ally) { bullet_a.Draw(*target); }
	//Lock UI 
	target->setView(target->getDefaultView());

	if (player->isAlive == true) {
		target->draw(scoreText);
		target->draw(objectiveText);
		player->DrawUI(*target);
		target->draw(killText);
		if (isKillstreak == true) {
			target->draw(killstreakText);
		}
		if (Airsupport > 0) {
			target->draw(airSupportText);
		}
	}


	if (isInarea == true) {
		for (Tank& tank_enemy : tanks_enemy) { 
			tank_enemy.DrawUI(*target); 
			target->draw(tankname);
		}
	}

	if (gameMode == 1 && countergameMode1 < 5) {
		target->draw(finalstageText);
	}

	if (isAppear == true) {
		target->draw(continueText);
		isContinue = true;
	}
	if (isAppear2 == true) {
		target->draw(continueText2);
		isContinue2 = true;
	}

	if (fade->isFade == true || fade->isBright == true) {
		fade->Draw(*target);
	}

	if (isInitial == true) {
		target->draw(black);
	}

	if (player->isAlive == false || tanks_ally[0].isAlive == false) {
		target->draw(gameover);
	}

	if (isEnd == true) {
		target->draw(victoryText);
	}

	//INTRODUCTION

	if (isBegin == true)
	{
		target->draw(dialogbox);
		target->draw(townsend);
		target->draw(dialogText);
		target->draw(pleaseEnter);
	}

	//Set Screen back
	target->setView(view);

	if (isPause == true) { // Pause Menu Render
		pauseMenu->Draw(*target);
	}
}
