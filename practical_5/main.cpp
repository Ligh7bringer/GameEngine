#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gameWidth = 600;
const int gameHeight = 800;

b2World* world;
const float physics_scale = 30.0f;
const float physics_scale_inv = -30.0f;

vector<b2Body*> bodies;
vector<RectangleShape*> sprites;

// convert from b2vec2 to vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
	return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}

//convert from vec2f to b2vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}

//convert from screen space.y to physics.y
inline const Vector2f invert_height(const Vector2f& in) {
	return Vector2f(in.x, gameHeight - in.y);
}

//create a box2d body with a box fixture
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const Vector2f& position, const Vector2f& size) {
	b2BodyDef bodyDef;
	//dynamic or static
	bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	bodyDef.position = sv2_to_bv2(position);
	//create the body
	b2Body* body = world.CreateBody(&bodyDef);

	//create fixture shape
	b2PolygonShape shape;
	shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y *0.5f);
	b2FixtureDef fixtureDef;
	//fixture properties
	fixtureDef.density = dynamic ? 10.f : 0.f;
	fixtureDef.friction = dynamic ? 0.8f : 1.f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	//add to body
	body->CreateFixture(&fixtureDef);
	return body;
}

//create a box2d body with a box fixture from a sf::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void Init() {	
	const b2Vec2 gravity(0.0f, -10.0f);
	world = new b2World(gravity);

	//create boxes
	for (int i = 1; i < 11; ++i) {
		//create shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * .7f));
		s->setSize(Vector2f(50.f, 50.f));
		s->setOrigin(Vector2f(25.f, 25.f));
		s->setFillColor(Color::Green);
		sprites.push_back(s);

		//create a dynamic body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		//give the box a spin
		b->ApplyAngularImpulse(5.f, true);
		bodies.push_back(b);
	}
}

void Load() {
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	world->Step(dt, 6, 2);

	for (int i = 0; i < bodies.size(); ++i) {
		sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
		sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
	}
}

void Render(RenderWindow &window) {
	for (const auto s : sprites) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(800, 600), "PHYSICS");

	Init();
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}