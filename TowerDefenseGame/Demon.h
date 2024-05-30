#pragma once
#include "GameObject.h"
#include "Waypoint.h"
#include "IObserver.h"
#include "Spell.h"

/*
Metrics du Demon (à effacer à la fin)
- Rectangle d'animation: 100 X 50
- Rayon du cercle de collision: hauteur du rectangle d'animation (50) divisé par 2
- Vitesse d'animation: 1 frame par 0.1 /secs
- Vitesse de déplacement: 0.9 + 0.1 X Numéro de vague (Si utilisation du DeltaTime, faire x60)
- Points de vie: 60 (50 pour la version à un développeur);
- Cadence de tir: un tir par (1.05 - 0.05 * numéro de vague) seconde.
- Portée du tir: 250
- Position de départ des démons au niveau 1: 610, -100
- Position de départ des démons au niveau 2: -100, 410
*/

class Demon: public GameObject, public IObserver
{
public:
	Demon();
	~Demon();
	bool init(Waypoint* waypoint, Waypoint* secondPath);
	void manageDemon(float deltaTime, int mapNbr, int currentWave);
	void spawn(Vector2f spawnPosition);
	void notify(Subject* subject) override;
	void draw(RenderWindow& renderWindow) const override;
	void damage(const float damage);

private:
	void setImages();
	void moveTowardsWaypoint(float deltaTime, int currentWave);
	void changeWaypoints(int mapNbr);
	void manageAnimation(const float deltaTime);
	void runAnimation(const float deltaTime, const float timePerFrame, const int imageNumber, const bool linear, IntRect* images);
	void manageSacredLight(Spell& spell);
	void managePlague(Spell& spell);
	void manageHealthBar();
	void resetModifiers();
	void manageDeath();
	

	enum AnimationState { FLY, DEATH };

	void setAnimationState(AnimationState animtionState);

	SoundBuffer attackBuffer;
	Sound attackSound;
	Texture texture;

	const int NBR_ANIM_IMAGES = 5;

	
	AnimationState animationState;

	float timeCounter = 0.0;
	int currentImage = 0;
	const float TIME_PER_FRAME = 0.1;

	IntRect* imagesFlying = nullptr;
	IntRect* imagesDying = nullptr;

	Waypoint* waypoint = nullptr;
	Waypoint* secondPath = nullptr;
	const int DEAD_ZONE = 3;

	float speed = 1.0f;
	float speedModifier = 1.0f;

	float damageModifier = 1.0f;

	bool isAffectedBySacredLight = false;
	bool isAffectedByPlague = false;

	Sprite redHealthBar;
	Sprite greenHealthBar;

	bool isDying = false;
	bool isTakingSecondPath = false;
};

