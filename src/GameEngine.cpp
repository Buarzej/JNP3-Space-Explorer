#include "GameEngine.h"
#include <time.h>
#include <stdexcept>

using D2D1::Point2F;

void GameEngine::InitializeAsteroid(Asteroid* asteroid) {

	// Generate rotation angle.
	asteroid->asteroid.SetAngle(rand() % 360);

	// Generate starting point.
	UINT maxRand = asteroid->fromSide ? maxY : maxX;
	if (asteroid->fromSide) {
		asteroid->asteroid.SetX(-asteroid->asteroid.GetWidth());
		asteroid->asteroid.SetY(rand() % (maxRand - 100));
	}
	else {
		asteroid->asteroid.SetX(rand() % (maxRand + 100));
		asteroid->asteroid.SetY(-asteroid->asteroid.GetHeight());
	}

	// Generate velocity.
	asteroid->vx = 2 * (rand() % 4 + 1);
	asteroid->vy = 2 * (rand() % 4 + 1);
}

BOOL GameEngine::CheckCollision(D2D1_RECT_F rc1, D2D1_RECT_F rc2) {
	if (rc1.left < rc2.right && rc1.right > rc2.left
		&& rc1.top < rc2.bottom && rc1.bottom > rc2.top)
		return TRUE;
	else
		return FALSE;
}

void GameEngine::GameOver() {
	gameRunning = FALSE;
}

GameEngine::GameEngine(GraphicsEngine* graphicsEngine)
	: graphicsEngine(graphicsEngine), gameRunning(FALSE)
{
	srand(time(NULL));

	spaceship = BitmapEntity(
		0, 0,
		48, 64,
		0.f,
		TEXT("../../../bitmaps/spaceship.png"));

	heading = TextEntity(
		25, 0,
		500, 80,
		0.f,
		TEXT("SpaceExplorer"),
		13,
		TEXT("Arial"),
		72.f,
		textColor
	);

	subheading = TextEntity(
		25, 0,
		500, 30,
		0.f,
		TEXT("Click to start"),
		15,
		TEXT("Arial"),
		36.f,
		textColor
	);

	background = GradientEntity(
		0, 0,
		0, 0,
		0.f,
		Point2F(0, 0),
		Point2F(0, 0),
		{ .position = 0.0f, .color = bgColor1 },
		{ .position = 1.0f, .color = bgColor2 }
	);

	for (SIZE_T i = 0; i < ASTEROID_COUNT; i++) {
		asteroids[i].asteroid = BitmapEntity(
			0, 0,
			((i % 4) + 1) * 32, ((i % 4) + 1) * 32,
			0.f,
			TEXT("../../../bitmaps/asteroid.png")
		);
		asteroids[i].fromSide = i % 2 ? TRUE : FALSE;
	}
}

GameEngine::~GameEngine() = default;

BOOL GameEngine::IsGameRunning() {
	return gameRunning;
}

void GameEngine::StartGame() {
	// Generate asteroids.
	for (Asteroid& asteroid : asteroids)
		InitializeAsteroid(&asteroid);

	gameRunning = TRUE;
}

void GameEngine::UpdateRelativeValues(INT mouseX, INT mouseY) {

	// Move spaceship to mouse position.
	spaceship.SetX(mouseX - spaceship.GetWidth() / 2);
	spaceship.SetY(mouseY - spaceship.GetHeight() / 2);
}

void GameEngine::UpdateRelativeValues(RECT wndRect) {
	maxX = wndRect.right - wndRect.left;
	maxY = wndRect.bottom - wndRect.top;

	background.SetWidth(maxX);
	background.SetHeight(maxY);
	background.SetGradStart(Point2F(0, 0));
	background.SetGradEnd(Point2F(0, maxY));

	heading.SetY(wndRect.bottom - 25
		- heading.GetHeight() - subheading.GetHeight());
	subheading.SetY(wndRect.bottom - 25 - subheading.GetHeight());
}

HRESULT GameEngine::RenderCurrState() {
	graphicsEngine->BeginDraw();
	graphicsEngine->DrawEntity(&background);

	if (gameRunning) {
		graphicsEngine->DrawEntity(&spaceship);
		for (Asteroid& asteroid : asteroids)
			graphicsEngine->DrawEntity(&asteroid.asteroid);
	}
	else {
		graphicsEngine->DrawEntity(&heading);
		graphicsEngine->DrawEntity(&subheading);
	}

	return graphicsEngine->EndDraw();
}

void GameEngine::GameTick() {
	for (Asteroid& asteroid : asteroids) {
		asteroid.asteroid.SetX(
			asteroid.asteroid.GetX() + asteroid.vx);
		asteroid.asteroid.SetY(
			asteroid.asteroid.GetY() + asteroid.vy);
		asteroid.asteroid.SetAngle(
			asteroid.asteroid.GetAngle() + 2.f);

		if (CheckCollision(
			spaceship.GetRect(), asteroid.asteroid.GetRect()))
			GameOver();
		else if (asteroid.asteroid.GetX() > maxX
			|| asteroid.asteroid.GetY() > maxY)
			InitializeAsteroid(&asteroid);
	}
}