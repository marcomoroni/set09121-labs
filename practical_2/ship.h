#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
	
	protected:
	sf::IntRect _sprite;
	Ship();
	
	public:
	
	explicit Ship(sf::IntRect ir);
	
	virtual ~Ship() = 0;
	
	virtual void Update(const float &dt);
};