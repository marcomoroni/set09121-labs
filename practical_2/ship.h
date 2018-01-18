#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	// Default constructor is hidden
	Ship();	
	bool _exploded;
public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;
	// Update, virtual so can be overrided, but not pure virtual
	virtual void Update(const float &dt);
	bool isExploded() const;
	virtual void Explode();
};

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
	static bool direction;
	static float speed;
};

class Player : public Ship {
public:
	Player();
	void Update(const float &dt) override;
	static float speed;
};