#pragma once
#include <SFML/Graphics.hpp>

struct Inputs
{
	Inputs()
	{
		reset();
	}

	void reset()
	{
		mousePosition = Vector2f(0.0f, 0.0f);
		mouseLeftButtonClicked = false;
		resetInstruction();
	}

	void resetInstruction() {
		createMageTower = false;
		createArcherTower = false;
		createPlagueSpell = false;
		createSacredLightSpell = false;
	}

	bool createMageTower;
	bool createArcherTower;
	bool createPlagueSpell;
	bool createSacredLightSpell;
	Vector2f mousePosition;
	bool mouseLeftButtonClicked;
};
