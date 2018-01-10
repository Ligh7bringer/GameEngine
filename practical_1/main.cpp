#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W, // Player 1 UP
	Keyboard::S, // P1 Down
	Keyboard::T, // P2 Up
	Keyboard::G // P2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float	ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];
Font font;
Text text;

int player1score = 0;
int player2score = 0;

void Reset() {
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x + 5, gameHeight / 2);

	//reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	ballVelocity = { server ? 100.0f : -100.0f, 60.0f };

	text.setString(to_string(player1score) + " : " + to_string(player2score));
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load() {
	//load font
	if (!font.loadFromFile("res/fonts/TravelingTypewriter.ttf")) {
		cout << "Couldn't load font!" << endl;
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(Color::White);

	//set size and origin of paddles
	for (auto &p_ : paddles) {
		p_.setSize(paddleSize - Vector2f(3, 3));
		p_.setOrigin(paddleSize / 2.f);	
	}

	// set size and origin of balls
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	Reset();
	
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

	//handle paddle movement
	float direction = 0.0f;
	float direction2 = 0.0f;

	// handle keyboard inputs
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction2--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction2++;
	}

	paddles[0].move(0, direction * paddleSpeed * dt);

	// "AI"
	if (paddles[1].getPosition().y < ball.getPosition().y) {
		direction2++;
	}
	else if (paddles[1].getPosition().y > ball.getPosition().y) {
		direction2--;
	}
	paddles[1].move(0, direction2 * paddleSpeed * dt);

	ball.move(ballVelocity * dt);

	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight) {
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);	
	}
	//right wall
	else if (bx > gameWidth) {
		server = false;
		player1score++;
		Reset();		
	}
	//left wall
	else if (bx < 0) {
		player2score++;
		server = true;
		Reset();		
	}
	else if (bx < paddleSize.x &&
			by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
			by < paddles[0].getPosition().y + (paddleSize.y * 0.5)) {
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;	
		ball.move(10, 0);
		cout << "LEFT paddle collision!" << endl;
	}
	else if (bx > paddles[1].getPosition().x &&
			by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
			by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
		cout << "RIGHT paddle collision" << endl;
	}
	
	if(paddles[0].getPosition().y + paddleSize.y / 2 > gameHeight || paddles[0].getPosition().y - paddleSize.y / 2 < 0) 
		paddles[0].move(0, -direction);
	if(paddles[1].getPosition().y + paddleSize.y / 2 > gameHeight || paddles[1].getPosition().y - paddleSize.y / 2 < 0) 
		paddles[1].move(0, -direction2);	
}

void Render(RenderWindow &window) {
	//draw
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

  int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }
