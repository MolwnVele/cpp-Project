#pragma once
#ifndef _PLAYERSCORE
#define _PLAYERSCORE

#include "GameObject.h"
#include <iostream>

using namespace std;

/*The "PlayerScore" class is a GameObject which holds the score for each player*/
class PlayerScore : public GameObject {
private:
	DuoFloater scorePosition; //2D vector for the position of the score.
	float fontSize; //size of the font of the score text
	string scoreText; //player's score
public:
	PlayerScore(const DuoFloater & scorePosition, float fontSize, const string & scoreText, const Color & scoreColor); //Constructor
	~PlayerScore(); //Destructor

	//Pure virtual function overriden for implementation
	void update() override;
	void draw() override;

	//Getter & setter
	string getScore() const { return scoreText; }
	void setScore(const string & scoreText) { this->scoreText = scoreText; }
};

#endif