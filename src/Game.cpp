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
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground", sf::Style::Default),
	m_tank(m_spriteSheetTexture, m_sprites)
{
	//m_window.setVerticalSyncEnabled(true);


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

	
	if (!m_playerTexture.loadFromFile("resources\\images\\E-100.png"))
	{
		//error
	}
	//m_player.setTexture(m_playerTexture);
	//m_player.setOrigin(103,48);
	m_player.setPosition(m_level.m_tank.m_position);

	if (!m_bgTexture.loadFromFile("resources\\images\\Background.jpg"))
	{
		//error
	}
	m_bgSprite.setTexture(m_bgTexture);

	if (!m_spriteSheetTexture.loadFromFile("resources\\images\\SpriteSheet.png"))
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
		sprite.setRotation(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}

	generateWalls();
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
		default:
			break;
		}
	}
}

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_spriteSheetTexture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

	m_tank.update(dt);
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
	//m_window.draw(m_player);
	m_tank.render(m_window);
	m_window.display();
}





