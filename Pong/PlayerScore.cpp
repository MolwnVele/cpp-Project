#include "PlayerScore.h"
#include "graphics.h"
#include "Initializer.h"
#include <iostream>

using namespace graphics;
using namespace std;

PlayerScore::PlayerScore(const DuoFloater & scorePosition, float fontSize, const string & scoreText, const Color & scoreColor) :
	scorePosition(scorePosition), fontSize(fontSize), scoreText(scoreText), GameObject(scoreColor) {}

PlayerScore::~PlayerScore() { cout << "Deleting PlayerScore Object..." << endl; }

//The score text is updated when a player scores by hitting the ball in the opposite "wall". A sound is playing when scoring.
void PlayerScore::update() {
	int tempPScore = stoi(scoreText);
	this->setScore(to_string(++tempPScore));
	playSound(string(SOUNDS_PATH) + "scoring.mp3", 0.7f, false);
}

//Drawing the player score in the canvas, using the SGG library
void PlayerScore::draw() {
	Brush scoreBrush;
	scoreBrush.fill_color[0] = getColor().r;
	scoreBrush.fill_color[1] = getColor().g;
	scoreBrush.fill_color[2] = getColor().b;
	setFont(string(FONTS_PATH) + "pong-score.ttf");
	drawText(scorePosition.x, scorePosition.y, fontSize, scoreText, scoreBrush);
}