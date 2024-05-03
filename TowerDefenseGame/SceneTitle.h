#pragma once
#include "Scene.h"
#include "Inputs.h"

using namespace sf;

class SceneTitle : public Scene
{
public:
	SceneTitle(RenderWindow& renderWindow, Event& event);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	void startGame();

	View view;

	Inputs inputs;

	Sprite titleScreen;
	Text instructions;
	Music themeSong;
};