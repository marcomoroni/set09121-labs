#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	// Update ALL bullets
	static void Update(const float &dt);
	// Constructor
	// (we never use this)
	Bullet(const sf::Vector2f &pos, const bool mode);
	// Render ALL bullets
	static void Render(sf::RenderWindow &window);
	// Choose an inactive bullet and use it
	static void Fire(const sf::Vector2f &pos, const bool mode);

	~Bullet()=default;
protected:
	// Never called by our code
	Bullet();
	//false = player bullet, true = inavder bullet
	bool _mode;
	// Pointer to the next bullet to spawn
	// Note: unsigned char go between 0 and 255, and then wrap round back to 0 and repeat
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	// Called by the static update
	void _Update(const float &dt);
};