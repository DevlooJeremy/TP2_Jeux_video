#pragma once
#include "Scene.h"
#include "Subject.h"
#include "IObserver.h"
#include "Hud.h"
#include "Inputs.h"
#include "TowerEmplacement.h"
#include "Tower.h"
#include "Waypoint.h"
#include "Demon.h"
#include "Spell.h"
#include "Projectile.h"

/*
Metrics de sceneGame OU du level 1 (à effacer à la fin)
- Position de la tour du roi: 1138, 600
- Position des emplacements de tour: (470, 170), (770, 250), (440, 370), (650, 520), (120, 650), (470, 700), (850, 710), (660, 950)
- Position des waypoints: (610, 8), (630, 222), (595, 444), (478, 514), (320, 558), (260, 620), (280, 720), (348, 812), (720, 830), (968, 850), (1110, 682)
- Position de départ des démons: 610, -100
- Nombre de démons : 20 (même si on doit en spawer 50, à 20 à la fois, le joueur en a plein les bras).
- Nombre et de chacun des types de projectiles: à vous de le décider mais il doit être raisonnable ET on ne doit jamais en manquer
- Temps de spawn entre les démons: de 1 à 3 secondes (60 à 180 rafraichissements) au hasard.
- Mana: 500 au départ, + 1 par 0.2 secondes (12 rafraichissements), + 25 mana par élimination de démon.
- Score: 50 par démon abbattu.  les dommages fait par les projectiles sont transférés en points.

- 50 éliminations de démons (donc 50 spawns pour gagner la scène)
*/

/*
Metrics de du level 2 (à effacer à la fin)
- Position de la tour du roi: 1138, 564
- Position des emplacements de tour: (110, 620), (228, 320), (444, 780), (362, 530), (610, 222), (998, 270), (630, 460), (935, 520), (798, 760),
- Position des waypoints: (88.f, 412.f), (168.f, 465.f), (222.f, 588.f), (308.f, 670.f), (424.f, 668.f), (double sortie: 510.f, 590.f);  
                          (478.f, 468.f), (516.f, 380.f), (594.f, 360.f), (806.f, 368.f), (1140.f, 450.f), (660.f, 598.f), (804.f, 650.f), (1140.f, 680.f),
- Position de départ des démons: -100, 410

- Le reste est identique à la scène 1
*/

class SceneGame : public Scene, public IObserver, public Subject
{
public:
	SceneGame(RenderWindow& renderWindow, Event& event, int currentWave);
	scenes run() override;
	bool init() override;
	void notify(Subject* subject);

	static enum Instruction {ARCHER_TOWER, MAGE_TOWER, PLAGUE, SACRED_LIGHT, NO_SELECTION};
	Instruction getInstruction() const;
	Vector2f getMousePosition() const;

	static const int NBR_DEMON = 20;
private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	void setupWaypoints();
	void manageDemon();
	void spawnDemon();

	void initTowers();
	void initProjectiles();
	
	void manageLeftClick();
	void managePlagePlacement();
	void manageSacredLightPlacement();
	void manageSpells();
	void manageTowers();
	void manageProjectiles();

	View view;
	Hud hud;
	Inputs inputs;

	Instruction instruction = NO_SELECTION;

	const int NBR_WAYPOINTS = 11;
	Waypoint waypoints[11];

	Demon demons[20];
	float spawnTimer = 0.0f;

	const int NB_SPELLS = 2;
	Spell spells[2];
	bool sacredLightCasted = false;
	bool plagueCasted = false;

	Sprite map;
	int mapNbr;

	static const int NBR_MAX_TOWER = 9;
	int currentMapMaxNbrOfTower;
	static const int NBR_TYPE_OF_ATTACK_TOWER = 2;
	const int KING_TOWER_ARRAY_POSITION = NBR_MAX_TOWER * NBR_TYPE_OF_ATTACK_TOWER;
	const Vector2f KING_TOWER_POSITION_MAP1 = Vector2f(1138, 600);
	const Vector2f KING_TOWER_POSITION_MAP2 = Vector2f(1138, 564);
	const Vector2f TOWER_EMPLACEMENTS_MAP1[NBR_MAX_TOWER] = { Vector2f(470, 170), Vector2f(770, 250), Vector2f(440, 370), Vector2f(650, 520), Vector2f(120, 650), Vector2f(470, 700), Vector2f(850, 710), Vector2f(660, 950) };
	const Vector2f TOWER_EMPLACEMENTS_MAP2[NBR_MAX_TOWER] = { Vector2f(110, 620), Vector2f(228, 320), Vector2f(444, 780), Vector2f(362, 530), Vector2f(610, 222), Vector2f(998, 270), Vector2f(630, 460), Vector2f(935, 520), Vector2f(798, 760) };
	TowerEmplacement emplacements[NBR_MAX_TOWER];
	Tower towers[NBR_MAX_TOWER * NBR_TYPE_OF_ATTACK_TOWER + 1];

	static const int NBR_MAX_TOWER_PROJECTILES = 10;
	static const int NBR_MAX_DEMON_PROJECTILES = 20;
	static const int NBR_TOTAL_MAX_PROJECTILES = NBR_MAX_TOWER_PROJECTILES * NBR_TYPE_OF_ATTACK_TOWER + NBR_MAX_DEMON_PROJECTILES;
	Projectile projectiles[NBR_TOTAL_MAX_PROJECTILES];
};