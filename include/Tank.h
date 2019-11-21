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
	Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites,std::vector<sf::Sprite>& targetSprites);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	void handleKeyInput();
	void increaseTurretRotation();
	void decreaseTurretRotation();
	void centreTurret();
	void fire(double dt);
	void bulletCollision();
	
	
	/// <summary>
	/// @brief Checks for collisions between the tank and the walls.
	/// 
	/// </summary>
	/// <returns>True if collision detected between tank and wall.</returns>
	bool checkWallCollision();

	/// <summary>
	/// @brief Stops the tank if moving and applies a small increase in speed in the opposite direction of travel.
	/// If the tank speed is currently 0, the rotation is set to a value that is less than the previous rotation value
	///  (scenario: tank is stopped and rotates into a wall, so it gets rotated towards the opposite direction).
	/// If the tank is moving, further rotations are disabled and the previous tank position is restored.
	/// The tank speed is adjusted so that it will travel slowly in the opposite direction. The tank rotation 
	///  is also adjusted as above if necessary (scenario: tank is both moving and rotating, upon wall collision it's 
	///  speed is reversed but with a smaller magnitude, while it is rotated in the opposite direction of it's 
	///  pre-collision rotation).
	/// </summary>
	void deflect();
	void adjustRotation();
	void setPosition(sf::Vector2f const& pos);

private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Sprite m_bullet;
	sf::Texture m_bulletTexture;
	sf::Texture const & m_texture;
	double m_speed{ 0.0 };
	double m_fireSpeed{ 1000 };
	double m_rotation{ 0.0 };
	double m_turretRotation{ 0.0 };
	double M_MAX{ 100.0 };
	double M_MIN{ -100.0 };
	bool m_central{ false };
	bool m_enableRotation{ true };
	bool m_fired{ false };
	bool m_canFire{ true };
	bool m_bulletMove{ false };
	sf::Vector2f m_previousPosition{ 0.0f,0.0f };
	double m_previousSpeed{ 0.0 };
	double m_previousRotation{ 0.0 };
	double m_previousTurretRotation{ 0.0 };
	//const sf::Vector2f m_targetPosition{ -1000,-1000 };
	std::vector<sf::Sprite>& m_wallSprites;
	std::vector<sf::Sprite>& m_targetSprites;
	sf::Vector2f dirVec{ -1,-1 };
		
};
