#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise player
	m_player.setRadius({ 10.f });
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({300.f,300.f});

	sf::Vector2u window_size = m_window.getSize();
	m_player.setPosition({
			window_size.x / 2.f - m_player.getRadius(),
			window_size.y / 2.f - m_player.getRadius()
		});
	// initialise food
	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Red);
	SpawnFood();
}

void Level::SpawnFood()
{
	sf::Vector2u window_size = m_window.getSize();
	float x = rand() % m_window.getSize().x;
	float y = rand() % m_window.getSize().y;
	m_food.setPosition({ x, y });
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
	if (m_isGameOver) return;

	m_timeTaken += dt;

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

		m_isGameOver = true;
		std::cout << "Game Over\nPoints" << m_foodEaten;
		std::cout << "\nTime Taken: " << m_timeTaken;

		//Reset player to center
		//m_player.setPosition({
			//window_size.x / 2.f - m_player.getRadius(),
			//window_size.y / 2.f - m_player.getRadius()
			//});

	}


	float radii_sum = m_player.getRadius() + m_food.getRadius();
	sf::Vector2f player_center = m_player.getPosition() + sf::Vector2f(m_player.getRadius(), m_player.getRadius());
	sf::Vector2f food_center = m_food.getPosition() + sf::Vector2f(m_food.getRadius(), m_food.getRadius());
	float x_diff = player_center.x - food_center.x;
	float y_diff = player_center.y - food_center.y;
	if (radii_sum * radii_sum > (x_diff * x_diff) + (y_diff * y_diff)) 
	{
		// They are colliding
		m_speed *= 1.2f;
		SpawnFood();
		std::cout << "yum";
		m_foodEaten++;
	}
}



// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_food);
	m_window.draw(m_player);
	endDraw();
}



