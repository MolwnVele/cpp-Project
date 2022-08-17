#pragma once
#ifndef _PADDLE
#define _PADDLE

#include "GameObject.h"

/*The "Paddle" class is a GameObject that represents the player (paddle)
  It can only move up and down.*/
class Paddle : public GameObject {
private:
	DuoFloater paddlePosition, paddleDimensions; //2D vectors representing the position and dimensions of the paddle
	float velocity = 8.f; //the velocity of the paddle. When the paddle moves, it happens at a constant speed, i.e no acceleration
	bool condition; /* A helper for the update function.
					  TRUE: Player 1 (Left Paddle)
					  FALSE: Player 2 (Right Paddle) */
public:
	Paddle(const DuoFloater & paddlePosition, const DuoFloater & paddleDimensions, const Color & paddleColor, bool condition); //Constructor
	~Paddle(); //Destructor
	//Pure virtual function overriden for implementation
	void update() override;
	void draw() override;

	//Getters & setters
	DuoFloater getPaddlePosition() const { return paddlePosition; }
	void setPaddlePosition(const DuoFloater & paddlePosition) { this->paddlePosition = paddlePosition; }
	
	DuoFloater getPaddleDimensions() const { return paddleDimensions; }
	void setPaddleDimensions(const DuoFloater & paddleDimensions) { this->paddleDimensions = paddleDimensions;  }
};

#endif