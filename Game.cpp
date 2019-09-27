/// <summary>
/// ----------------------------------------------
/// Name: Allexis Alvarico
/// Date: 20/09/19
/// ----------------------------------------------
/// Summary: This Excerise is to create a sprite
/// and to move, rotate it and set its origin
/// ----------------------------------------------
/// Estimated Time: 30mins
/// Actual Time:
/// Known Bugs:
/// 
/// </summary>





#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);


	int currentLevel = 1;

	// Will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	if (!m_playerTexture.loadFromFile("E-100.png"))
	{
		//error
	}
	m_player.setTexture(m_playerTexture);
	m_player.setOrigin(103,48);
	m_player.setPosition(m_level.m_tank.m_position);

	if (!m_bgTexture.loadFromFile("Background.jpg"))
	{
		//error
	}
	m_bgSprite.setTexture(m_bgTexture);

	if (!m_spriteSheetTexture.loadFromFile("SpriteSheet.png"))
	{

		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}

	// Extract the wall image from the spritesheet.
	sf::Sprite sprite;
	sf::IntRect wallRect(2, 129, 33, 23);
	sprite.setTexture(m_spriteSheetTexture);
	sprite.setTextureRect(wallRect);
	// Loop through each Obstacle instance - recall that Obstacles are structs
	for (auto& obstacle : m_level.m_obstacles)
	{
		// Position the wall sprite using the obstacle data
		sprite.setPosition(obstacle.m_position);
		sprite.rotate(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		//case sf::Keyboard::Right:
		//	m_turn++;
		//	m_player.setRotation(m_turn);
		//	// Up key was pressed...
		//	break;
		//case sf::Keyboard::Left:
		//	m_turn--;
		//	m_player.setRotation(m_turn);
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{



}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	m_window.draw(m_bgSprite);
	int i = 0;
	for (auto& obstacle : m_level.m_obstacles)
	{
		m_window.draw(m_sprites.at(i));
		i++;
	}
	m_window.draw(m_player);

	m_window.display();
}





