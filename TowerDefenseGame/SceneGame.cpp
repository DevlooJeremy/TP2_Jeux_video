#include "SceneGame.h"
#include "ContentPipeline.h"
#include <iostream>

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event, int currentWave) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->currentWave = currentWave;
	Subject::addObserver(this);
}

Scene::scenes SceneGame::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;

	return transitionToScene;
}

bool SceneGame::init()
{	
	if (currentWave % 2 != 0)
		mapNbr = 1;
	else
		mapNbr = 2;

	if (mapNbr == 1)
		map.setTexture(ContentPipeline::getInstance().getMapTexture(Maps::map1));
	else
		map.setTexture(ContentPipeline::getInstance().getMapTexture(Maps::map2));

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont());
	setupWaypoints();
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		int secondPath = rand() & 2 + 1;
		Waypoint* path;
		if (secondPath == 1) path = &waypoints[6];
		else path = &waypoints[11];
		demons[i].init(&waypoints[0], path);
		Subject::addObserver(&demons[i]);
	}


	initTowers();
	initProjectiles();

	return true;
}

void SceneGame::getInputs()
{
	inputs.reset();
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				inputs.mouseLeftButtonClicked = true;
				inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
			}
		}

		if (event.type == Event::KeyPressed)
		{
			if (event.key.scancode == Keyboard::Scan::Z) //Archer tower
			{
				instruction = Instruction::ARCHER_TOWER;
			}

			if (event.key.scancode == Keyboard::Scan::X) //Mage tower
			{
				instruction = Instruction::MAGE_TOWER;
			}

			if (event.key.scancode == Keyboard::Scan::A) //Plague
			{
				instruction = Instruction::PLAGUE;
			}

			if (event.key.scancode == Keyboard::Scan::S) //Sacred light
			{
				instruction = Instruction::SACRED_LIGHT;
			}

			if (event.key.scancode == Keyboard::Scan::W)
			{
				inputs.toggleWapointsClicked = true;
			}
		}
	}
}

void SceneGame::update()
{
	manageLeftClick();
	manageDemon();
	manageSpells();
	manageTowers();
	manageProjectiles();
	manageWaypoints();
	manageMana();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.draw(map);

	for (int i = 0; i < currentMapMaxNbrOfTower; i++)
	{
		emplacements[i].draw(renderWindow);
		towers[i].draw(renderWindow);
		towers[i + currentMapMaxNbrOfTower].draw(renderWindow);
	}

	towers[KING_TOWER_ARRAY_POSITION].draw(renderWindow);

	if (showWaypoints) 
	{
		if (mapNbr == 1)
		{
			for (size_t i = 0; i < NBR_WAYPOINTS_FIRST_MAP; i++)
			{
				renderWindow.draw(waypoints[i]);
			}
		}
		else
		{
			for (size_t i = 0; i < NBR_WAYPOINTS; i++)
			{
				renderWindow.draw(waypoints[i]);
			}
		}
	}

	for (size_t i = 0; i < NB_SPELLS; i++)
	{
		spells[i].draw(renderWindow);
	}

	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].draw(renderWindow);
	}

	for (int i = 0; i < NBR_TOTAL_MAX_PROJECTILES; i++)
	{
		projectiles[i].draw(renderWindow);
	}

	hud.draw(renderWindow);
	renderWindow.display();

}

bool SceneGame::unload()
{

	Subject::removeAllObservers();
	return true;
}

SceneGame::Instruction SceneGame::getInstruction() const {
	return this->instruction;
}

Vector2f SceneGame::getMousePosition() const {
	return inputs.mousePosition;
}

void SceneGame::manageLeftClick() {
	if (inputs.mouseLeftButtonClicked)
	{
		notifyAllObservers();
		switch (instruction)
		{
		case PLAGUE:
			managePlagePlacement();
			break;

		case SACRED_LIGHT:
			manageSacredLightPlacement();
			break;

		default:
			break;
		}
	}
}

void SceneGame::managePlagePlacement()
{
	for (size_t i = 0; i < NB_SPELLS; i++)
	{
		if (!spells[i].isActive())
		{
			if (spells[i].castPlague(inputs.mousePosition)) mana -= PLAGUE_COST;
			break;
		}
	}
}

void SceneGame::manageSacredLightPlacement()
{
	for (size_t i = 0; i < NB_SPELLS; i++)
	{
		if (!spells[i].isActive())
		{
			if (spells[i].castSacredLight(inputs.mousePosition)) mana -= SACRED_LIGHT_COST;
			break;
		}
	}
}

void SceneGame::manageSpells()
{
	for (size_t i = 0; i < NB_SPELLS; i++)
	{
		spells[i].manageSpell(deltaTime);
	}
}

void SceneGame::manageTowers() {
	for (int i = 0; i < currentMapMaxNbrOfTower*2; i++)
	{
		towers[i].shoot(demons, NBR_DEMON, deltaTime);
	}
}

void SceneGame::manageProjectiles() {
	for (int i = 0; i < NBR_MAX_TOWER_PROJECTILES*2; i++)
	{
		projectiles[i].follow(deltaTime);
	}
}

void SceneGame::setupWaypoints() 
{
	if (mapNbr == 1)
	{
		waypoints[0].setPosition(610, 8);
		waypoints[1].setPosition(630, 222);
		waypoints[2].setPosition(595, 444);
		waypoints[3].setPosition(478, 514);
		waypoints[4].setPosition(320, 558);
		waypoints[5].setPosition(260, 620);
		waypoints[6].setPosition(280, 720);
		waypoints[7].setPosition(348, 812);
		waypoints[8].setPosition(720, 830);
		waypoints[9].setPosition(968, 850);
		waypoints[10].setPosition(1110, 682);

		for (size_t i = 0; i < NBR_WAYPOINTS_FIRST_MAP - 1; i++)
		{
			waypoints[i].setNext(&waypoints[i + 1]);
		}
	}
	else
	{
		waypoints[0].setPosition(88.f, 412.f);
		waypoints[1].setPosition(168.f, 465.f);
		waypoints[2].setPosition(222.f, 588.f);
		waypoints[3].setPosition(308.f, 670.f);
		waypoints[4].setPosition(424.f, 668.f);
		waypoints[5].setPosition(510.f, 590.f); //double sortie
		waypoints[6].setPosition(478.f, 468.f); //choix 1
		waypoints[7].setPosition(516.f, 380.f);
		waypoints[8].setPosition(594.f, 360.f);
		waypoints[9].setPosition(806.f, 368.f);
		waypoints[10].setPosition(1140.f, 450.f);
		waypoints[11].setPosition(660.f, 598.f); // choix 2
		waypoints[12].setPosition(804.f, 650.f);
		waypoints[13].setPosition(1140.f, 680.f);

		for (size_t i = 0; i < NBR_WAYPOINTS - 1; i++)
		{
			waypoints[i].setNext(&waypoints[i + 1]);
		}
		waypoints[5].setNext(nullptr);
		waypoints[10].setNext(nullptr);
	}

	
}

void SceneGame::manageDemon()
{
	for (size_t i = 0; i < NBR_DEMON; i++)
	{
		demons[i].manageDemon(deltaTime, mapNbr, currentWave);
	}
	spawnDemon();
}

void SceneGame::spawnDemon()
{
	spawnTimer += deltaTime;
	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0.0f;
		for (size_t i = 0; i < NBR_DEMON; i++)
		{
			if (!demons[i].isActive()) 
			{
				Vector2f position;
				if (mapNbr == 1) position = Vector2f(610, -100);
				else position = Vector2f(-100, 410);
				demons[i].spawn(position);
				demonSpawned += 1;
				break;
			}

		}
	}
}

void SceneGame::initTowers() {
	if (mapNbr == 1)
	{
		currentMapMaxNbrOfTower = 8;
		towers[KING_TOWER_ARRAY_POSITION].init(Tower::KING_TOWER_SPRITE_NBR, KING_TOWER_POSITION_MAP1);
		for (int i = 0; i < currentMapMaxNbrOfTower; i++)
		{
			emplacements[i].init(TOWER_EMPLACEMENTS_MAP1[i]);
			towers[i].init(Tower::ARCHER_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP1[i]);
			towers[i + currentMapMaxNbrOfTower].init(Tower::MAGE_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP1[i]);
		}
	}
	else
	{
		currentMapMaxNbrOfTower = NBR_MAX_TOWER;
		towers[KING_TOWER_ARRAY_POSITION].init(Tower::KING_TOWER_SPRITE_NBR, KING_TOWER_POSITION_MAP2);
		for (int i = 0; i < currentMapMaxNbrOfTower; i++)
		{
			emplacements[i].init(TOWER_EMPLACEMENTS_MAP2[i]);
			towers[i].init(Tower::ARCHER_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP2[i]);
			towers[i + currentMapMaxNbrOfTower].init(Tower::MAGE_TOWER_SPRITE_NBR, TOWER_EMPLACEMENTS_MAP2[i]);
		}
	}
}

void SceneGame::initProjectiles() {
	for (int i = 0; i < NBR_TOTAL_MAX_PROJECTILES; i++)
	{
		projectiles[i].init(Projectile::ARROW_SPRITE_NBR);
		projectiles[i + NBR_MAX_TOWER_PROJECTILES].init(Projectile::BLAST_SPRITE_NBR);
		projectiles[i + NBR_MAX_TOWER_PROJECTILES * 2].init(Projectile::FIREBALL_SPRITE_NBR);
	}
}

void SceneGame::notify(Subject* subject) {
	if (typeid(*subject) == typeid(Tower))
	{
		Tower* tower = static_cast<Tower*>(subject);
		if (tower->isShooting())
		{
			int indexMultiplier = 0;
			switch (tower->getTowerType())
			{
			case Tower::MAGE_TOWER_SPRITE_NBR:
				indexMultiplier = 1;
				break;
			}

			for (int i = 0; i < NBR_MAX_TOWER_PROJECTILES; i++)
			{
				int index = i + NBR_MAX_TOWER_PROJECTILES * indexMultiplier;
				if (!projectiles[index].isActive())
				{
					projectiles[index].shoot(&demons[tower->getClosestDemonIndex()], tower->getPosition());
					break;
				}
			}
		}
	}
}

void SceneGame::manageWaypoints()
{
	if (inputs.toggleWapointsClicked)
	{
		if (showWaypoints) showWaypoints = false;
		else showWaypoints = true;
	}
}

void SceneGame::manageMana()
{
	if (manaTimer >= 0.2)
	{
		mana += 1;
		manaTimer = 0.0f;
	}
	manaTimer += deltaTime;
	hud.setMana(mana);
}