#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	void Update(const float &dt);
	Bullet(const sf::Vector2f &pos, const bool mode);
	~Bullet()=default;
protected:
	Bullet();
	//false = player bullet, true = inavder bullet
	bool _mode;
	// Pointer to the next bullet to spawn
	// Note: unsigned char go between 0 and 255, and then wrap round back to 0 and repeat
	static unsigned char bulletPointer;
	static Bullet bullets[256];
};