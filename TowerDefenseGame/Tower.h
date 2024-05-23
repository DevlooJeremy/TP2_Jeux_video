#pragma once
#include "GameObject.h"

/*
Metrics des tours  (à effacer à la fin)

- Rayon du cercle de collision: taille en X du sprite ou du rectangle d'animation divisé par 4
- Points de vie: Tour du roi: 500, autres: 250.
- Cadence de tir: tour d'archer: 0.8 secondes entre les tirs (48 rafraichissements d'écran à 60 fps), tour de mage, 1.5 seconde et demi (90 rafraichissements)
- Portée de tir: 300 chacunes

- Rectangle d'animation de la tour du mage: 150 X 150
- Vitesse d'animation de la tour du mage: 0.15 Secs
- L'image 0 est l'image idle. Quand on initie le tir, on passe tout de suite à l'image 1.
*/


class Tower : public GameObject
{
public:
	Tower();
	~Tower();
	void init(const int spriteNbr, const Vector2f& position);

	void build();

	static const int KING_TOWER_SPRITE_NBR = 1;
	static const int ARCHER_TOWER_SPRITE_NBR = 2;
	static const int MAGE_TOWER_SPRITE_NBR = 3;

private:
	const float KING_MAX_HEALTH = 500;
	const float MAX_HEALTH = 250;
	
	float health;

	const int MAGE_RECTANGLE_SIZE = 150;
	const int MAGE_ATTACK_ANIM = 3;
	IntRect* imagesMageAttack = nullptr;
	void setupMageAnims();
};

