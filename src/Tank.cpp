#include "Tank.h"
#include "CollisionDetector.h"
#include <iostream>

Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites)
: m_texture(texture), m_wallSprites(wallSprites)
{
	initSprites(m_tankBase.getPosition());
}

void Tank::update(double dt)
{	
	handleKeyInput();
	m_previousPosition = m_tankBase.getPosition();
	m_tankBase.setPosition(m_tankBase.getPosition().x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt/ 1000), m_tankBase.getPosition().y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	m_turret.setPosition(m_tankBase.getPosition().x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000), m_tankBase.getPosition().y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	m_tankBase.setRotation(m_rotation);
	m_turret.setRotation(m_turretRotation);
	m_speed *= 0.99;
	m_speed = std::clamp(m_speed, M_MIN, M_MAX);


	if (checkWallCollision())
	{
		deflect();
	}


}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::increaseSpeed()
{
	m_previousSpeed = m_speed;
	m_speed += 1;

}

void Tank::decreaseSpeed()
{
	m_previousSpeed = m_speed;
	m_speed -= 1;
	
}

void Tank::increaseRotation()
{

	m_previousRotation = m_rotation; // NEW
	m_rotation += 0.5;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
	
}

void Tank::decreaseRotation()
{
	m_previousRotation = m_rotation; // NEW
	m_rotation -= 0.5;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}

}

void Tank::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		m_central = true;
	}

	if (m_central)
	{
		centreTurret();
	}

}

void Tank::increaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation; // NEW
	m_turretRotation += 0.5;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation; // NEW
	m_turretRotation -= 0.5;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}

void Tank::centreTurret()
{
	if (m_turretRotation < m_rotation)
	{
		m_turretRotation += 1;
	}
	else if (m_turretRotation > m_rotation)
	{
		m_turretRotation -= 1;
	}
	else
	{
		//m_turretRotation += 0;
		m_central = false;
	}

	
}


bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) ||
			CollisionDetector::collision(m_tankBase, sprite))
		{
			std::cout << "I have collided with a wall\n";
			return true;
		}
	}
	std::cout << "I have not collided with a wall\n";
	return false;
}
void Tank::deflect()
{
	// In case tank was rotating.
	adjustRotation();

	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
}
void Tank::adjustRotation()
{
	// If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_turretRotation = m_previousTurretRotation;
	}
}

void Tank::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);

}