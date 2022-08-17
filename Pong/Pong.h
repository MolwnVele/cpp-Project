#pragma once
#include "Ball.h"
#include "PlayerScore.h"
#include "Paddle.h"
#include "Image.h"
#include "ColorPicker.h"
#include "Initializer.h"
#include <map>

using namespace std;

/*The "Pong" class encapsulates all GameObject objects under a single unit. This is where the two main things happen:
	1. Drawing the necessary components.
	2. Updating the components depending on the actions that happen by the players.
 Four levels are drawn and updated based on the GameStatus value.
*/
class Pong {
private:

	//Creating the basic Pong components using pointers
	Ball* pongBall = nullptr;
	PlayerScore* scoreP1 = nullptr, * scoreP2 = nullptr;
	Paddle* playerOne = nullptr, * playerTwo = nullptr;
	//Map Collection initializations for the images and the Color Pickers (buttons)
	map<int, Image*> images;
	map<int, ColorPicker*> colorPickers;
	map<int, ColorPicker*>::iterator CPIT; //ColorPicker iterator
	//These bool variables help detecting if the Pong components exist at the point of checking.
	bool initNet = false, initPlayers = false, initBall = false, initScores = false;
	GameStatus status; //a GameStatus variable which holds the state of the game.
	string controls[5] = { "Move Up (Player One) :           W", "Move Down (Player One) :           S", "Move Up (Player Two) :           ARROW UP", "Move Down (Player Two) :           ARROW DOWN",
	"Pause Game :           P"}; //a string array which holds the controls / key tutorial, shown at the starting screen
	pair<pair<string, int>, int> winner; /*a pair consisting of two parts: 1) A pair with the data types of string and integer and 2) another integer.
										   The first part holds the winner of the game and the score of the winner
										   The second part is the index value for the colorPickers data structure, in order to access it properly*/

	//The different draw and update methods for each game state
	//1. Start Screen
	void drawStartScreen();
	void updateStartScreen();

	//2. Game Screen
	void drawGameScreen();
	void updateGameScreen();

	//3. Pause Screen
	void drawPauseScreen();
	void updatePauseScreen();

	//4. End Screen
	void drawEndScreen();
	void updateEndScreen();

	pair<pair<string, int>, int> getWinner() const; //Method to find the winner of the game
	int getLoser() const; //Method to find the loser of the game
public:
	Pong(); //Default constructor
	~Pong(); //Destructor
	//The 2 main functions that control the four different game states, update() & control()
	void draw();
	void update();
};