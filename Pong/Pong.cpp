#include "Pong.h"
#include "graphics.h"
#include <iostream>

using namespace graphics;

Pong::Pong() {}

/*The destructor will release / free up memory by destroying the pointer to class instances
The maps cannot be deleted like the pointers, so we use map's clear() method to make their size 0. */
Pong::~Pong() {
	if (pongBall) {
		delete pongBall;
		pongBall = nullptr;
	}
	if (playerOne) {
		delete playerOne;
		playerOne = nullptr;
	}
	if (playerTwo) {
		delete playerTwo;
		playerTwo = nullptr;
	}
	if (scoreP1) {
		delete scoreP1;
		scoreP1 = nullptr;
	}
	if (scoreP2) {
		delete scoreP2;
		scoreP2 = nullptr;
	}
	images.clear();
	colorPickers.clear();
}

//Depending on the game state, the corresponding screen drawing will be executed.
void Pong::draw() {
	switch (status) {
	case STATUS_START:
		drawStartScreen();
		break;
	case STATUS_PLAYING:
		drawGameScreen();
		break;
	case STATUS_PAUSE:
		drawPauseScreen();
		break;
	case STATUS_END:
		drawEndScreen();
		break;
	default:
		cout << "Invalid status" << endl;
	}
}

//Depending on the game state, the corresponding screen update will be executed.
void Pong::update() {
	switch (status) {
		case STATUS_START:
			updateStartScreen();
			break;
		case STATUS_PLAYING:
			updateGameScreen();
			break;
		case STATUS_PAUSE:
			updatePauseScreen();
			break;
		case STATUS_END:
			updateEndScreen();
			break;
		default:
			cout << "Invalid status" << endl;
	}
}

//--------------------------------------------------------------------------- START SCREEN ------------------------------------------------------------------------------------------------------------------------

/*The main focus of the start screen is the Color Customization on the left and the Tutorial (Controls / Keys) Display on the tutorial.
  Other graphical components are also added for appeal.*/
void Pong::drawStartScreen() {
	//Drawing the images
	Brush BR;
	images.insert({ 0, new Image({ CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 8 }, { 325.0f, 190.0f }, "pong_logo.png") });
	images.insert({ 1, new Image({ CANVAS_WIDTH / 15.0f, CANVAS_HEIGHT - 25.0f }, { 162.5f, 130.0f }, "atari.png") });
	images[0]->drawImage();
	images[1]->drawImage();

	//Showing the command to start the game and some notices.
	BR.texture = "";
	setFont(string(FONTS_PATH) + "EightBitDragon.ttf");
	drawText(CANVAS_WIDTH / 2.8f, CANVAS_HEIGHT / 2.95f, 30.f, "Press ENTER to start!", BR);
	drawText(CANVAS_WIDTH / 2.625f, CANVAS_HEIGHT - 15.f, 14.f, "A tribute to the original creator ALLAN ALCORN", BR);
	drawText(CANVAS_WIDTH / 1.185f, CANVAS_HEIGHT - 15.f, 14.f, "AUTHOR: Dimitrios Fillipou", BR);

	//Setting up the Color Customization feature
	BR.fill_color[0] = 0.86f;
	BR.fill_color[1] = 0.86f;
	BR.fill_color[2] = 0.86f;
	drawText(CANVAS_WIDTH / 3.85f, CANVAS_HEIGHT / 2.3f, 17.f, "COLOR CUSTOMIZATION", BR);
	/* 1st Element -> Left paddle color
	   2nd Element -> Right paddle color
	   3rd Element -> Net color
	   4th Element -> Ball color
	*/
	colorPickers.insert({ 0, new ColorPicker({ CANVAS_WIDTH / 4.f, CANVAS_HEIGHT / 1.945f }, 23.0f, "Player One : ", { 1.0f }, { CANVAS_WIDTH / 2.5f, CANVAS_HEIGHT / 1.985f }, { 40.f }) });
	colorPickers.insert({ 1, new ColorPicker({ CANVAS_WIDTH / 4.f, CANVAS_HEIGHT / 1.635f }, 23.0f, "Player Two : ", { 1.0f }, { CANVAS_WIDTH / 2.5f, CANVAS_HEIGHT / 1.665f }, { 40.f }) });
	colorPickers.insert({ 2, new ColorPicker({ CANVAS_WIDTH / 4.f, CANVAS_HEIGHT / 1.405f }, 23.0f, "Net Color : ", { 1.0f }, { CANVAS_WIDTH / 2.5f, CANVAS_HEIGHT / 1.425f }, { 40.f }) });
	colorPickers.insert({ 3, new ColorPicker({ CANVAS_WIDTH / 4.f, CANVAS_HEIGHT / 1.225f }, 23.0f, "Ball Color : ", { 1.0f }, { CANVAS_WIDTH / 2.5f, CANVAS_HEIGHT / 1.245f }, { 40.f }) });
	for (CPIT = colorPickers.begin(); CPIT != colorPickers.end(); CPIT++) (*CPIT).second->draw(); //using the iterator to draw the color selections.
	
	//Showing the tutorial
	drawText(CANVAS_WIDTH / 1.55f, CANVAS_HEIGHT / 2.3f, 17.f, "CONTROLS / KEYS", BR);
	BR.fill_color[0] = 1.f;
	BR.fill_color[1] = 1.f;
	BR.fill_color[2] = 1.f;
	int i;
	float j;
	int arraySize = sizeof(controls) / sizeof(*controls);
	//This loop is done in a way that there is equal vertical space in between the texts.
	for (i = 0, j = 0.f; i < arraySize; ++i, j += 0.12f) {
		if (i >= 4) j -= 0.03f;
		drawText(CANVAS_WIDTH / 1.55f, CANVAS_HEIGHT / (2.f - j), 16.f, controls[i], BR);
	}
}

/*From the start screen we can only go to the game screen (start the game) or prematurely ending the app with the ESC button (default of the CMD)
  Based on the colors we chose for the pong components (Paddles + Score, Ball) the correct color will be applied.
  The color of the net is set on Game Screen drawing, which is the 3rd element of the colorPickers map!*/
void Pong::updateStartScreen() {
	//If the user pressed the "ENTER" button, the game status is changed to STATUS_PLAYING and a sound is played for "ambience"
	if (getKeyState(SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		playSound(string(SOUNDS_PATH) + "start.wav", 0.95f, false);
	}
	//Making the buttons work
	if (!colorPickers.empty()) for (CPIT = colorPickers.begin(); CPIT != colorPickers.end(); CPIT++) (*CPIT).second->update();
	//Applying the colors to the components
	if (initPlayers && !colorPickers.empty()) {
		pongBall->setColor(colorPickers[3]->getColor());
		playerOne->setColor(colorPickers[0]->getColor());
		scoreP1->setColor(colorPickers[0]->getColor());
		playerTwo->setColor(colorPickers[1]->getColor());
		scoreP2->setColor(colorPickers[1]->getColor());
	}
}

//--------------------------------------------------------------------------- GAME SCREEN ------------------------------------------------------------------------------------------------------------------------

/*The Game Screen contains the game and its logic:
 DRAWN:
	-> 2 paddles, one on the left and one on the right with their corresponding scores on the upper left and right
	-> The net and the ball at the center*
 LOGIC:
	-> The ball starts moving from the middle to the right side and the players aim to hit a goal on the opponent's side (hitting the opponent's back "walls".
	   When this happens, the player's score is increased.
	-> Since the game is playing for an infinite amount of time, someone can end the game by pressing the F1 button.
	-> To pause the game, someone will need to press the P button and then the game state is changed to STATUS_PAUSE
 */

//Drawing the game screen as described above.
void Pong::drawGameScreen() {
	//NET
	Brush netBrush;
	netBrush.outline_color[0] = colorPickers[2]->getColor().r;
	netBrush.outline_color[1] = colorPickers[2]->getColor().g;
	netBrush.outline_color[2] = colorPickers[2]->getColor().b;
	/*An algorithm to create the dotted lines, representing the net.
		-> When the y-coordinate is not a multiple of 8 and line is drawn
		-> After the drawing, there is gap of 5 pixels.
	*/
	for (int y = 0; y < CANVAS_HEIGHT; ++y) {
		if (!(y % 8)) {
			drawLine(CANVAS_WIDTH / 2.f, (float)y, CANVAS_WIDTH / 2.f, (float)(y + 5), netBrush);
		}
	}

	//BALL
	/*Since the game is running on a loop via the startMessagingLoop() in mainPong.cpp, we need to make sure that the objects are created once, especially if they are pointer to objects created with "new"
	  In this way, we prevent memory leaking. The bool variables will help us with this and this action is done for all the main Pong components.*/
	if (!initBall) {
		pongBall = new Ball({ CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f }, { BALL_WIDTH, BALL_HEIGHT }, 0.0f, colorPickers[3]->getCPColor());
		initBall = true;
	}
	pongBall->draw();

	//PADDLES
	if (!initPlayers) {
		playerOne = new Paddle({ 50.f, CANVAS_HEIGHT / 2.f }, { PADDLE_WIDTH, PADDLE_HEIGHT }, colorPickers[0]->getCPColor(), true);
		playerTwo = new Paddle({ CANVAS_WIDTH - 50.f, CANVAS_HEIGHT / 2.f }, { PADDLE_WIDTH, PADDLE_HEIGHT }, colorPickers[1]->getCPColor(), false);
		initPlayers = true;
	}
	playerOne->draw();
	playerTwo->draw();

	//PLAYER SCORES
	if (!initScores) {
		scoreP1 = new PlayerScore({ CANVAS_WIDTH / 4.f, 85.f }, 70.f, "0", colorPickers[0]->getColor());
		scoreP2 = new PlayerScore({ 3 * CANVAS_WIDTH / 4.f, 85.f }, 70.f, "0", colorPickers[1]->getColor());
		initScores = true;
	}
	scoreP1->draw();
	scoreP2->draw();
}

/*Updating the game screen depending on the actions that happen there*/
void Pong::updateGameScreen() {
	/*Calling the appropriate update methods from the game components.
		-> Paddle Movement
		-> Ball Movement
	*/
	playerOne->update();
	playerTwo->update();
	pongBall->update();
	//Collision Detection. A sound is played when a collision is detected.
	Collision colP1B, colP2B, colWB;
	if (pongBall && playerOne && playerTwo) {
		colP1B = pongBall->detectPaddleCollision(*playerOne);
		if (colP1B != None) {
			pongBall->collideWithPaddle(colP1B);
			playSound(string(SOUNDS_PATH) + "pong_hit.wav", 0.85f, false);
		}
		colP2B = pongBall->detectPaddleCollision(*playerTwo);
		if (colP2B != None) {
			pongBall->collideWithPaddle(colP2B);
			playSound(string(SOUNDS_PATH) + "pong_hit.wav", 0.85f, false);
		}
		//Updating the score depending on if the ball hit the left or right "wall". Else the ball hit either the top or bottom "wall"
		colWB = pongBall->detectWallCollision();
		if (colWB != None) {
			pongBall->collideWithWall(colWB);
			if (colWB == Left) scoreP2->update();
			else if (colWB == Right) scoreP1->update();
			else playSound(string(SOUNDS_PATH) + "wall_hit.wav", 0.85f, false);
		}
	}
	/*The original Pong's score limit was 11 (just like the Ping Pong game / offical rules). A player can win by reaching 11 points.
	  A suitable ending screen will appear (the ending screen will be drawn with the drawEndScreen() method.
	  The only thing we can do, is to play a sound depending on the result.*/
	if (stoi(scoreP1->getScore()) == 11 || stoi(scoreP2->getScore()) == 11) {
		status = STATUS_END;
		winner = getWinner(); //Getting the winner of the game or draw if there is none.
		playMusic(string(SOUNDS_PATH) + "victory.mp3", 0.85f, false);
	}
	/*The game session can be paused by pressing the P button.
	  When it is pressed the game state is changed to STATUS_PAUSE and a sound is played for ambience.*/
	if (getKeyState(SCANCODE_P)) {
		status = STATUS_PAUSE;
		playSound(string(SOUNDS_PATH) + "pause&resume.wav", 0.95f, false);
	}
}

//--------------------------------------------------------------------------- PAUSE SCREEN ------------------------------------------------------------------------------------------------------------------------

/*The Pause Screen is a very simple screen, only showing two things:
	-> The "PAUSED" message"
	-> A command to resume playing
*/

//Drawing the end screen as described above
void Pong::drawPauseScreen() {
	Brush pauseBrush;
	pauseBrush.fill_color[0] = 0.86f;
	pauseBrush.fill_color[1] = 0.86f;
	pauseBrush.fill_color[2] = 0.86f;
	setFont(string(FONTS_PATH) + "EightBitDragon.ttf");
	drawText(CANVAS_WIDTH / 2.f - 115.f, CANVAS_HEIGHT / 2.f, 55.f, "PAUSED", pauseBrush);
	drawText(CANVAS_WIDTH / 2.f - 147.f, CANVAS_HEIGHT / 1.8f, 20.f, "(Press R to resume game!)", pauseBrush);
}

/*To resume playing, a player must press the R button.
  When this happens the game state is changed back to STATUS_PLAYING and a sound is played for ambience. */
void Pong::updatePauseScreen() {
	if (getKeyState(SCANCODE_R)) {
		status = STATUS_PLAYING;
		playSound(string(SOUNDS_PATH) + "pause&resume.wav", 0.95f, false);
	}
}

//--------------------------------------------------------------------------- END SCREEN ------------------------------------------------------------------------------------------------------------------------

/*In the End Screen, a message will be shown, detailing who won and what the score was. A golden cup will also be shown, just for appeal.
  Also:
	1. The same images and notices from the start screen wil appear here.
	2. A command for restarting the game will be shown.
*/

//Drawing the End Screen as described above.
void Pong::drawEndScreen() {
	Brush endBrush;
	endBrush.fill_color[0] = 1.0f;
	endBrush.fill_color[1] = 1.0f;
	endBrush.fill_color[2] = 1.0f;
	setFont(string(FONTS_PATH) + "EightBitDragon.ttf");
	images[0]->drawImage();
	images[1]->drawImage();

	Brush winnerBrush;
	winnerBrush.fill_color[0] = colorPickers[winner.second]->getColor().r;
	winnerBrush.fill_color[1] = colorPickers[winner.second]->getColor().g;
	winnerBrush.fill_color[2] = colorPickers[winner.second]->getColor().b;
	drawText(CANVAS_WIDTH / 4.55f, CANVAS_HEIGHT / 2.75f, 55.f, winner.first.first + " WON the game!", winnerBrush);
	//Displaying the correct score depending on who won.
	float correction;
	if (winner.first.second == 11 && getLoser() == 10) correction = 125.f;
	else correction = 100.f;

	if (winner.second == 0) drawText(CANVAS_WIDTH / 2.f - correction, CANVAS_HEIGHT / 1.85f, 75.f, to_string(winner.first.second) + " - " + to_string(getLoser()), endBrush);
	else drawText(CANVAS_WIDTH / 2.f - correction, CANVAS_HEIGHT / 1.85f, 75.f, to_string(getLoser()) + " - " + to_string(winner.first.second), endBrush);
	
	//Showing the golden trophy image
	images.insert({ 2, new Image({ CANVAS_WIDTH / 1.945f, CANVAS_HEIGHT / 1.525f }, { 238.f / 3.f, 250.f / 3.f }, "trophy.png") });
	images[2]->drawImage();
	//Showing the restart game command
	drawText(CANVAS_WIDTH / 2.55f, CANVAS_HEIGHT / 1.25f, 20.f, "Press F1 to restart the game!", endBrush);
	
	//Draw the notices
	drawText(CANVAS_WIDTH / 2.625f, CANVAS_HEIGHT - 15.f, 14.f, "A tribute to the original creator ALLAN ALCORN", endBrush);
	drawText(CANVAS_WIDTH / 1.185f, CANVAS_HEIGHT - 15.f, 14.f, "AUTHOR: Dimitrios Fillipou", endBrush);
}

/*Other than closing the map (either by pressing the X in the window or pressing the ESC button) we are able to restart the game by pressing the F1 button.
  Restarting the game means that every component that was changed during the game must be resetted to its original values.
  When the F1 button is pressed the status is changed to STATUS_START, a sound is played for ambience and the resetting in initiated from there on.*/
void Pong::updateEndScreen(){
	if (getKeyState(SCANCODE_F1)) {
		status = STATUS_START;
		playSound(string(SOUNDS_PATH) + "restart.wav", 0.95f, false);
		//Resetting the net color
		colorPickers[2]->setColor({ 1.f });
		//Resetting the paddles' position and color
		playerOne->setPaddlePosition({ 50.f, CANVAS_HEIGHT / 2.f });
		playerOne->setColor({ 1.f });
		playerTwo->setPaddlePosition({ CANVAS_WIDTH - 50.f, CANVAS_HEIGHT / 2.f });
		playerTwo->setColor({ 1.f });
		//Resetting the score
		scoreP1->setScore("0");
		scoreP1->setColor({ 1.f });
		scoreP2->setScore("0");
		scoreP2->setColor({ 1.f });
		//Resetting the ball's position, velocity and color.
		pongBall->setBallPosition({ CANVAS_WIDTH / 2.f, CANVAS_HEIGHT / 2.f });
		pongBall->setBallVelocity({ 5.f, 0.f });
		pongBall->setColor({ 1.f });
		//In the start screen the buttons should be resetted back to having a white color.
		for (CPIT = colorPickers.begin(); CPIT != colorPickers.end(); CPIT++) (*CPIT).second->setColor({ 1.f });
	}
}

//--------------------------------------------------------------------------- UTILITIES ------------------------------------------------------------------------------------------------------------------------

/*Some helper methods to get the winner and the loser of the game.*/

//Finding the winner of the game. The type of value that is returned is described on Pong.h
pair<pair<string, int>, int> Pong::getWinner() const {
	int scorePlayerOne = stoi(scoreP1->getScore()); //stoi -> conversion from string to int
	int scorePlayerTwo = stoi(scoreP2->getScore());
	//if (scorePlayerOne > scorePlayerTwo) {
	if (scorePlayerOne == 11){
		pair<string, int> pair("Player One", scorePlayerOne);
		return make_pair(pair, 0); //a different way of creating a pair<> variable
	}
	else {
		pair<string, int> pair("Player Two", scorePlayerTwo);
		return make_pair(pair, 1);
	}
}

//Finding the loser of the game. The loser's score is returned.
int Pong::getLoser() const {
	int scorePlayerOne = stoi(scoreP1->getScore());
	int scorePlayerTwo = stoi(scoreP2->getScore());
	if (scorePlayerOne > scorePlayerTwo) return scorePlayerTwo;
	else return scorePlayerOne;
}