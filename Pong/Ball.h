#pragma once
#ifndef _BALL
#define _BALL

#include "GameObject.h"
#include "Initializer.h"
#include "Paddle.h"

/*The "Ball" class is a GameObject that represents the pong ball. 
  It is movable and can collide with the players (paddles) and the "walls"*/
class Ball : public GameObject {
private:
	DuoFloater ballPosition, ballDimensions; //2D vectors for the position and dimensions of the ball
	DuoFloater ballVelocity = { 5.f, 0.f }; // default/initial velocity of the ball. It's not controlled by the player but depends on the collisions.
	float penetration; /* the penetration value will allow us to combat a collision problem with the paddle:
					   If it didn't exist, the ball would occassionally get stuck in the paddle when a collision is detected and the ball's velocity is reversed,
					   but another collision would be immediately detected before it leaves the paddle.*/
public:
	Ball(const DuoFloater & ballPosition, const DuoFloater & ballDimensions, float penetration, const Color & ballColor); //Constructor
	~Ball(); //Destructor
	
	//Pure virtual function overriden for implementation
	void draw() override;
	void update() override;

	//Getters & setters
	DuoFloater getBallPosition() const { return ballPosition; }
	void setBallPosition(const DuoFloater & ballPosition) { this->ballPosition = ballPosition; }

	DuoFloater getBallDimensions() const { return ballDimensions; }
	void setBallDimensions(const DuoFloater & ballDimensions) { this->ballDimensions = ballDimensions; }
	
	float getPenetration() { return penetration; }
	void setPenetration(float penetration) { this->penetration = penetration; }
	
	DuoFloater getBallVelocity() const { return ballVelocity; }
	void setBallVelocity(const DuoFloater & ballVelocity) { this->ballVelocity = ballVelocity; }

	void collideWithPaddle(Collision collision); //"Execute" the collision between the ball and a paddle
	void collideWithWall(Collision collision); //"Execute" the collision between the ball and the "walls"

	//Since we are using an argument, the class of which has not been created at this point, we using "class" and we promise to create the class.
	Collision detectPaddleCollision(const class Paddle & player); //Detect the collision between the ball and a paddle.
	Collision detectWallCollision(); //Detect the collision between the ball and the "walls"
};
#endif