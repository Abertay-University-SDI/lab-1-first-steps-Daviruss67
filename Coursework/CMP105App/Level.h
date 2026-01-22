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
	sf::CircleShape m_player;

	// Default variables for level class.
	int m_speed = 200;
};