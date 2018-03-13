#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Things to remember about Box2D:
//     1. B2D has its own Vector maths classes that we munvert to/from.
//     2. B2D's positive y is towards the top of the screen.
//     3. B2D's has a scale. We render things in pixel.
//        Usually Sam uses 1 unit = 1 meter when working on 3D games.
//        Box2D has a recommended 30 units per 1 pixel that feels realistic.

const int gameWidth = 1000;
const int gameHeight = 800;

b2World* world;
const float physics_scale = 30.f; //                                          ?
const float physics_scale_inv = 1 / physics_scale;
const int velocityIterations = 2; //                                          ?
const int positionIterations = 2; //                                          ?

vector<b2Body*> bodies;
vector<RectangleShape*> sprites;



// Conversion helper functions ------------------------------------------------

// Convert from b2Vec2 to a Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in)
{
	return Vector2f(in.x * physics_scale, in.y * physics_scale);
}

// Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in)
{
	return b2Vec2(in.x * physics_scale_inv, in.y * physics_scale_inv);
}

// Convert from Screenspave.y to physics.y
inline const Vector2f invert_height(const Vector2f& in)
{
	return Vector2f(in.x, gameHeight - in.y);
}

// ----------------------------------------------------------------------------



// Helper to add a body to the scene ------------------------------------------

// Create a Box2D body with a box fixture
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic,
	const Vector2f& position, const Vector2f size)
{
	b2BodyDef BodyDef;
	// Is it dynamic (moving) or static (stationary)?
	BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(position);
	// Create the body
	b2Body* body = world.CreateBody(&BodyDef);

	// Create the fixure shape
	b2PolygonShape Shape;
	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);

	// Fixture properties
	b2FixtureDef FixtureDef;
	FixtureDef.density = dynamic ? 10.f : 0.f;
	FixtureDef.friction = dynamic ? 0.8f : 1.f;
	FixtureDef.restitution = 1.0f;
	FixtureDef.shape = &Shape;

	// Add to body
	body->CreateFixture(&FixtureDef);
	return body;
}

// Create a Box2D body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic,
	const RectangleShape& rs)
{
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

// ----------------------------------------------------------------------------



void init()
{
	const b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world, which holds and simulates the physics bodies
	world = new b2World(gravity);

	// Wall dimentions
	Vector2f walls[] = {
		// Top (position, size)
		Vector2f(gameWidth * .5f, 5.f), Vector2f(gameWidth, 10.f),
		// Bottom
		Vector2f(gameWidth * .5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
		// Left
		Vector2f(5.f, gameHeight * .5f), Vector2f(10.f, gameHeight),
		// Right
		Vector2f(gameWidth - 5.f, gameHeight * .5f), Vector2f(10.f, gameHeight)
	};

	// Build walls
	for (int i = 0; i < 7; i += 2)
	{
		// Create SFML shapes for each wall
		auto s = new RectangleShape();
		s->setPosition(walls[i]);
		s->setSize(walls[i + 1]);
		s->setOrigin(Vector2f(walls[i + 1].x / 2, walls[i + 1].y / 2));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, false, *s);
		bodies.push_back(b);
	}

	// Create boxes
	for (int i = 1; i < 11; ++i)
	{
		// Create SFML shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * .7f));
		s->setSize(Vector2f(50.f, 50.f));
		s->setOrigin(Vector2f(25.f, 25.f));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		// Give the box a spin
		b->ApplyAngularImpulse(5.f, true);
		bodies.push_back(b);
	}
}



void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Step physics world by dt
	world->Step(dt, velocityIterations, positionIterations);

	for (int i = 0; i < bodies.size(); ++i)
	{
		// Sync sprites to physics position
		sprites[i]->setPosition(
			invert_height(bv2_to_sv2(bodies[i]->GetPosition()))
		);
		// Sync sprites to physics rotation
		sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
	}
}



void Render(RenderWindow &window)
{
	for (auto s : sprites) window.draw(*s);
}



int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PHYSICS");
	init();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}