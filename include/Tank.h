#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const & texture, sf::Vector2f const & pos);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;
	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };
	double M_MAX{ 100.0 };
	double M_MIN{ -100.0 };
	double m_friction{ 5.0 };
		
};
