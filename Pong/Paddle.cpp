#include "Paddle.h"
#include "graphics.h"
#include "Initializer.h"
#include <iostream>

using namespace std;
using namespace graphics;

Paddle::Paddle(const DuoFloater & paddlePosition, const DuoFloater & paddleDimensions, const Color & paddleColor, bool condition) :
	paddlePosition(paddlePosition), paddleDimensions(paddleDimensions), GameObject(paddleColor), condition(condition) {}

Paddle::~Paddle() { cout << "Deleting Paddle object..." << endl; }

/*The paddle position is updated via certain key presses, in other words we need to detect certain key inputs
  The "condition" variable will help us setting the position on the y-axis depending on which player is moving.*/
void Paddle::update() {
	/*condition = TRUE => Left Paddle (Player 1) moves => Detect W and S key presses and set the position accordingly 
	  condition = FALSE => Right Paddle (Player 2) moves => Detect ARROW UP and ARROW DOWN key presses and set the position accordingly */
	if (condition) {
		if (getKeyState(SCANCODE_W)) paddlePosition.y -= velocity * getDeltaTime() / 10.f;
		if (getKeyState(SCANCODE_S)) paddlePosition.y += velocity * getDeltaTime() / 10.f;
	}
	else {
		if (getKeyState(SCANCODE_UP)) paddlePosition.y -= velocity * getDeltaTime() / 10.f;
		if (getKeyState(SCANCODE_DOWN)) paddlePosition.y += velocity * getDeltaTime() / 10.f;
	}
	//Restricting the top and bottom of the screen based on the canvas dimensions.
	if (paddlePosition.y < PADDLE_HEIGHT) paddlePosition.y = PADDLE_HEIGHT;
	if (paddlePosition.y > CANVAS_HEIGHT - PADDLE_HEIGHT) paddlePosition.y = CANVAS_HEIGHT - PADDLE_HEIGHT;
}

//Drawing the paddles using the SGG library
void Paddle::draw() {
	Brush paddleBrush;
	paddleBrush.fill_color[0] = getColor().r;
	paddleBrush.fill_color[1] = getColor().g;
	paddleBrush.fill_color[2] = getColor().b;
	paddleBrush.outline_opacity = 0.f;
	drawRect(paddlePosition.x, paddlePosition.y, paddleDimensions.w, paddleDimensions.h, paddleBrush);
}