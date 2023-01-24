#ifndef SPACESHOOTER_GAME_ENGINE_H
#define SPACESHOOTER_GAME_ENGINE_H

#include "GraphicsEngine.h"

class GameEngine {

	static const SIZE_T ASTEROID_COUNT = 20;

	struct Asteroid {
		BitmapEntity asteroid;
		INT vx, vy;
		BOOL fromSide;
	};

	GraphicsEngine* graphicsEngine;
	BOOL gameRunning;
	INT maxX, maxY;

	BitmapEntity spaceship;
	Asteroid asteroids[ASTEROID_COUNT];

	GradientEntity background;
	TextEntity heading;
	TextEntity subheading;

private:
	void InitializeAsteroid(Asteroid* asteroid);

	BOOL CheckCollision(D2D1_RECT_F rc1, D2D1_RECT_F rc2);

	void GameOver();

public:
	GameEngine(GraphicsEngine* graphicsEngine);

	~GameEngine();

	BOOL IsGameRunning();

	void StartGame();

	void UpdateRelativeValues(INT mouseX, INT mouseY);

	void UpdateRelativeValues(RECT wndRect);

	HRESULT RenderCurrState();

	void GameTick();
};

#endif // SPACESHOOTER_GAME_ENGINE_H