#include <Box2D\Box2D.h>

// Things to remember about Box2D:
//     1. B2D has its own Vector maths classes that we munvert to/from.
//     2. B2D's positive y is towards the top of the screen.
//     3. B2D's has a scale. We render things in pixel.
//        Usually Sam uses 1 unit = 1 meter when working on 3D games.
//        Box2D has a recommended 30 units per 1 pixel that feels realistic.

b2World* world;

void init()
{
	const b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world, which holds and simulates the physics bodies
	world = new b2World(gravity);
}

int main() {
	return 0;
}