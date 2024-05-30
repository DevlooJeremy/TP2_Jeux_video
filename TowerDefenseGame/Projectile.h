#pragma once
#include "GameObject.h"
#include "IObserver.h"

/*
Metrics du Projectile (à effacer à la fin)

- Vitesse de déplacement (framerate 60 fps): Arrow: 15, blast 8, fireball: 10
(Si utilisation du DeltaTime, faire x60 à ces valeurs)

- Dommages: les projectiles font les dommages random suivants
  Arrow: 1 à 4, blast 1 à 12, fireball: 1 à 10

- Cadence de tir: un tir à tous les 
  Arrow: 48 rafraichissements / 0.8 secondes
  Blast: 90 rafraichissements / 1.5 secondes
  Fireball: 63 - 3 * wave / 1.05 secondes - 0.05 * wave
*/

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();
	void init(const int spriteNbr);

	static const int ARROW_SPRITE_NBR = 1;
	static const int BLAST_SPRITE_NBR = 2;
	static const int FIREBALL_SPRITE_NBR = 3;

	void shoot(GameObject* target, const Vector2f origin);
	void follow(const float deltaTime);
private:
	int spriteNbr;
	
	const int ARROW_SPEED = 15 * 60;
	const int BLAST_SPEED = 8 * 60;
	const int FIREBALL_SPEED = 10 * 60;
	
	const int MIN_DAMAGE = 1;
	const int ARROW_MAX_DAMAGE = 4;
	const int BLAST_MAX_DAMAGE = 12;
	const int FIREBALL_MAX_DAMAGE = 10;
	
	/*
	const float ARROW_SHOT_SPEED = 0.8;
	const float BLAST_SHOT_SPEED = 1.5;
	const float FIREBALL_BASE_SHOT_SPEED = 1.05;
	const float FIREBALL_SHOT_SPEED_MODIFIER = 0.05;
	*/

	int speed;
	int maxDamage;
	GameObject* target = nullptr;
	int getRndDamage() const;
};

