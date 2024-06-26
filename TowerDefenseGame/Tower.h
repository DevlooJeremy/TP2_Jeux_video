#pragma once
#include "GameObject.h"
#include "IObserver.h"
#include "Subject.h"

/*
Metrics des tours  (� effacer � la fin)

- Rayon du cercle de collision: taille en X du sprite ou du rectangle d'animation divis� par 4
- Points de vie: Tour du roi: 500, autres: 250.
- Cadence de tir: tour d'archer: 0.8 secondes entre les tirs (48 rafraichissements d'�cran � 60 fps), tour de mage, 1.5 seconde et demi (90 rafraichissements)
- Port�e de tir: 300 chacunes

- Rectangle d'animation de la tour du mage: 150 X 150
- Vitesse d'animation de la tour du mage: 0.15 Secs
- L'image 0 est l'image idle. Quand on initie le tir, on passe tout de suite � l'image 1.
*/


class Tower : public GameObject, public IObserver, public Subject
{
public:
	Tower();
	~Tower();
	void init(const int spriteNbr, const Vector2f& position);
	void notify(Subject* subject);
	void draw(RenderWindow& renderWindow) const override;

	void build();
	void takeDamage(const int damage);
	void shoot(const GameObject demons[], const int nbrOfDemons, const float deltaTime);

	bool isShooting() const;
	int getClosestDemonIndex() const;
	int getTowerType() const;
	bool asBeenBuilt() const;

	static const int KING_TOWER_SPRITE_NBR = 1;
	static const int ARCHER_TOWER_SPRITE_NBR = 2;
	static const int MAGE_TOWER_SPRITE_NBR = 3;

	static const int ARCHER_MANA_COST = 70;
	static const int MAGE_MANA_COST = 100;
private:
	int spriteNbr;

	const float KING_MAX_HEALTH = 500;
	const float MAX_HEALTH = 250;
	Sprite redHealthBar;
	Sprite greenHealthBar;
	void manageHealthBar();

	const int MAGE_RECTANGLE_SIZE = 150;
	const int MAGE_ATTACK_ANIM = 3;
	IntRect* imagesMageAttack = nullptr;
	bool finishedAnimations = true;
	bool playedAnim = false;
	bool facingLeft = false;
	void setupMageAnims();
	void manageMageAnims(float deltaTime);
	enum AnimationState { IDLE, ATTACK };
	AnimationState state;
	int lastRect = 0;
	const float MAX_DELAY= 0.5;
	float animStateDelay = 0;

	bool towerBuiltOnPosition = false;
	bool mouseInBound(const Vector2f mousePosition) const;
	bool built = false;

	const int RANGE = 300;
	int closestDemonIndex;
	const float ARCHER_MAX_SHOT_COOLDOWN = 0.8;
	const float MAGE_MAX_SHOT_COOLDOWN = 1.5;
	float maxShotCooldown;
	int ASBonus = 1;
	float shotCooldown = 0;
	bool shooting = false;

	void managePlague(const int damage, const int bonusDamage);
	void manageSacredLight(const int bonusASpeed, const int healing);
	int damageMultiplier = 1;
};

