#pragma once
#include "Subject.h"
#include "GameObject.h"

/*
Metrics du Spell (� effacer � la fin)
- Port�e des deux types de Spell: 400
- Dur�e de vie des deux spells: 5 secondes
- Vitesse de rotation:
  augmente de 

va de 0 � 20, progressivement en avancant dans le temps
- Ajoute 1/15 � la rotation � chaque rafraichissement d'�cran.
- Ajoute deltaTime / 15 � chaque update si on utilise le deltaTime

- Couleur transmise par la peste: Color(96, 241, 76, 255);
- Couleur transmise par la sacred light: Color(214, 172, 2, 255);

*/

class Spell: public Subject, public GameObject
{

public:
	Spell();
	float getRange() const;
	void manageSpell(const float deltaTime);
	bool castSacredLight(const Vector2f position);
	bool castPlague(const Vector2f position);
	void draw(RenderWindow& renderWindow) const override;
	float getSlow() const;
	int getDamage() const;
	int getHealing() const;
	int getBonusDamage() const;
	int getAttackSpeedBonus() const;


	enum SpellType { PLAGUE, SACRED_LIGHT };
	SpellType getSpellType();
	

private:
	void cast(Vector2f position);
	void manageDuration(const float deltaTime);
	void manageRunes();
	void setDamage();
	void setHealing();


	SpellType spellType;
	const float RANGE = 400.0f;
	Sprite rune;

	int damage;
	int heal;


	const int MINIMUM_HEAL = 6;
	const int MAXIMUM_HEAL = 15;
	const int MIN_DAMAGE = 1;
	const int MAXIMUM_SACRED_LIGHT_DAMAGE = 5;
	const int MAXIMUM_PLAGUE_DAMAGE = 10;

	const float SLOW = 0.5f;
	const int ATTACK_SPEED_BONUS = 2;
	const int BONUS_DAMAGE = 2;

	float timer = 0;
	static bool sacredLightCasted;
	static bool plagueCasted;
};

