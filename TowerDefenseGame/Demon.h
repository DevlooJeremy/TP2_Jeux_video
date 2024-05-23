#pragma once
#include "GameObject.h"
#include "Waypoint.h"
#include "IObserver.h"

/*
Metrics du Demon (� effacer � la fin)
- Rectangle d'animation: 100 X 50
- Rayon du cercle de collision: hauteur du rectangle d'animation (50) divis� par 2
- Vitesse d'animation: 1 frame par 0.1 /secs
- Vitesse de d�placement: 0.9 + 0.1 X Num�ro de vague (Si utilisation du DeltaTime, faire x60)
- Points de vie: 60 (50 pour la version � un d�veloppeur);
- Cadence de tir: un tir par (1.05 - 0.05 * num�ro de vague) seconde.
- Port�e du tir: 250
- Position de d�part des d�mons au niveau 1: 610, -100
- Position de d�part des d�mons au niveau 2: -100, 410
*/

class Demon: public GameObject, public IObserver
{
public:
	Demon();
	~Demon();
	bool init(Waypoint* waypoint);
	void manageDemon(float deltaTime);
	void spawn();
	void notify(Subject* subject) override;
private:
	void setImages();
	void moveTowardsWaypoint(float deltaTime);
	void changeWaypoints();
	void manageAnimation(const float deltaTime);
	void runAnimation(const float deltaTime, const float timePerFrame, const int imageNumber, const bool linear, IntRect* images);
	

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
	const int DEAD_ZONE = 3;

	float speed = 0.9f;
};

