#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	enum class movement { UP, DOWN, LEFT, RIGHT};
	movement m_buttonPressed;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void SpawnFood();

	// Default variables for level class.
	int m_speed = 200;
	sf::CircleShape m_player;
	sf::CircleShape m_food;
	int m_foodEaten = 0;
	float m_timeTaken = 0.f;
	bool m_isGameOver = false;
};