#include "Ball.h"
#include "graphics.h"
#include <iostream>

using namespace std;
using namespace graphics;

Ball::Ball(const DuoFloater & ballPosition, const DuoFloater & ballDimensions, float penetration, const Color & ballColor) :
	ballPosition(ballPosition), ballDimensions(ballDimensions), penetration(penetration), GameObject(ballColor) {}

Ball::~Ball() { cout << "Deleting Ball Object..." << endl; }

//Drawing the ball, using the SGG library
void Ball::draw() {
	Brush ballBrush;
	ballBrush.fill_color[0] = getColor().r;
	ballBrush.fill_color[1] = getColor().g;
	ballBrush.fill_color[2] = getColor().b;
	ballBrush.outline_opacity = 0.0f;
	drawRect(ballPosition.x, ballPosition.y, ballDimensions.w, ballDimensions.h, ballBrush);
}

//Updating the position of the ball (make it move) based on its velocity.
void Ball::update() { ballPosition += {ballVelocity.x * getDeltaTime() / 10.f, ballVelocity.y * getDeltaTime() / 30.0f};}

/*Depending on the paddle zone / zone of collision detection, we use this method to reflect differently. 
  When the ball hits the middle there is no change to the y-coordiate of the velocity.*/
void Ball::collideWithPaddle(Collision collision) {
	ballPosition.x += penetration;
	ballVelocity.x = -ballVelocity.x; //Velocity negation, thus creating a reflection

	//The value on the left of the ballVelocity.y indicates the angle of the collision.
	switch (collision) {
	case Top:
		ballVelocity.y = -0.75f * 25.f;
		break;
	case Middle:
		ballVelocity.y = 0.f;
		break;
	case Bottom:
		ballVelocity.y = 0.75f * 25.f;
		break;
	default:
		cout << "Error, invalid collision type" << endl;
		break;
	}
}

/*Similar to the collideWithPaddle() method. If the ball collided with the left or the right "wall" the ball is resetted to the cneter
  and moves to the side of the loser.*/
void Ball::collideWithWall(Collision collision) {
	if (collision == Top || collision == Bottom){
		ballPosition.y += penetration;
		ballVelocity.y = -ballVelocity.y;
	}
	else {
		//Simulating the spawn of the ball after scoring like in the original Pong
		ballPosition = { CANVAS_WIDTH / 2.f, ballPosition.y };
		if (collision == Left) ballVelocity = { -5.f, ballVelocity.y };
		else if (collision == Right) ballVelocity = { 5.f, ballVelocity.y };
	}
}

/*Since the Paddle and the ball are rectangular, we are using the Separating Axes Theorem (SAT).
-> This theorem simply suggests that if we can show that the projections of two objects onto an axis have a certain gap, then the objects are not colliding.
-> What we want do is project (cast a "shadow") from each object ti each axis, so we have
	1) Project from the ball onto the x- and y-axis and,
	2) Project from the paddle onto the x- and y-axis.
   If we can find even a single axis on which the projections don't "touch", then objects definetely don't collide.
-> To simulate this projection we need the x- coordinates of the left and right of the paddle and the ball (projection onto the x-axis)
   as well as the y-coordinates of the top and bottom of the paddle and the ball (projection onto the y-axis).
 */
Collision Ball::detectPaddleCollision(const Paddle & player)
{
	float ballLeft = ballPosition.x;
	float ballRight = ballPosition.x + BALL_WIDTH + 6.f;
	float ballTop = ballPosition.y;
	float ballBottom = ballPosition.y + BALL_HEIGHT + 6.f;

	float paddleLeft = player.getPaddlePosition().x;
	float paddleRight = player.getPaddlePosition().x + PADDLE_WIDTH + 2.0f;
	float paddleTop = player.getPaddlePosition().y - 15.0f;
	float paddleBottom = player.getPaddlePosition().y + PADDLE_HEIGHT - 10.0f;

	Collision collision{}; //Initializing a Collision value. By default, its value is "None".

	//One of these conditions is met, when there is no collision based on the SAT.
	if (ballLeft >= paddleRight) return collision;
	if (ballRight <= paddleLeft) return collision;
	if (ballTop >= paddleBottom) return collision;
	if (ballBottom <= paddleTop) return collision;

	//Finding the penetration.
	float paddleRangeUpper = paddleBottom - (3.f * PADDLE_HEIGHT / 4.f);
	float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 4.f);

	if (ballVelocity.x < 0.f) penetration = (paddleRight - ballLeft); //left paddle
	else if (ballVelocity.x > 0.f) penetration = (paddleLeft - ballRight); //right paddle

	//Finding the paddle zone / zone of collision detection. The ball can hit either the middle or one of the two edges.
	if ((ballBottom > paddleTop) && (ballBottom <= paddleRangeUpper)) collision = Top;
	else if ((ballBottom < paddleRangeMiddle)) collision = Middle;
	else collision = Bottom;

	return collision;
}

/*To detect the collision of the ball with the walls we just need to check the edges of the ball with the 4 positions in the canvas, LEFT, RIGHT, TOP and BOTTOM.
  Again we need the x-coordinates of the left and right of the ball and the y-coordinates of the top and bottom. */
Collision Ball::detectWallCollision()
{
	float ballLeft = ballPosition.x;
	float ballRight = ballPosition.x + BALL_WIDTH + 2.f;
	float ballTop = ballPosition.y;
	float ballBottom = ballPosition.y + BALL_HEIGHT + 2.f;

	Collision collision{};

	/*If the ball hit the left or right "wall" we don't need to find the penetration since it means that someone scored.
	  Finding the penetration depth is only important when the ball hits to top and bottom "walls" because of the bouncing that must occur.*/
	if (ballLeft < 0.0f) collision = Left;
	else if (ballRight > CANVAS_WIDTH) collision = Right;
	else if (ballTop < 0.0f) {
		penetration = -ballTop;
		collision = Top;
	}
	else if (ballBottom > CANVAS_HEIGHT) {
		penetration = CANVAS_HEIGHT - ballBottom;
		collision = Bottom;
	}

	return collision;
}