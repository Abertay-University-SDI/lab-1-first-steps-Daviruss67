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

	if (m_player.getPosition().x > m_window.getSize().x || m_player.getPosition().x < 0) 
	{
		m_player.setPosition({ 400,300 });
	}
	else if (m_player.getPosition().y > m_window.getSize().y || m_player.getPosition().y < 0) 
	{
		m_player.setPosition({ 400,300 });
	}

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

