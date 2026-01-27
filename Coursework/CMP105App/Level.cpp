#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius({ 10.f });
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({300.f,300.f});

}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::D)) 
	{
		m_buttonPressed = movement::RIGHT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A)) 
	{
		m_buttonPressed = movement::LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		m_buttonPressed = movement::UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_buttonPressed = movement::DOWN;
	}


}

// Update game objects
void Level::update(float dt)
{
	switch (m_buttonPressed)
	{
	case movement::UP:
		m_player.move({ 0.f, -m_speed * dt });
		break;
	case movement::DOWN:
		m_player.move({ 0.f, m_speed * dt });
		break;
	case movement::RIGHT:
		m_player.move({ m_speed * dt, 0.f });
		break;
	case movement::LEFT:
		m_player.move({ -m_speed * dt, 0.f });
	}

	// Check for wall collision
	sf::Vector2u window_size = m_window.getSize();
	sf::Vector2f snake_pos = m_player.getPosition();
	if (snake_pos.x < 0 || snake_pos.y < 0 || snake_pos.x + 2 * m_player.getRadius() > window_size.x
		|| snake_pos.y + 2 * m_player.getRadius() > window_size.y) 
	{
		//Reset player to center
		m_player.setPosition({
			window_size.x / 2.f - m_player.getRadius(),
			window_size.y / 2.f - m_player.getRadius()
			});

	}

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

