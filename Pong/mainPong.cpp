#include "graphics.h"
#include "Initializer.h"
#include "Pong.h"

using namespace std;
using namespace graphics;

//Via the Pong object (pongGame / pointer to Pong class) we call its draw function to operate depending on the game state
void draw() {
	Pong* pongGame = reinterpret_cast<Pong*>(getUserData()); //returns the user-submitted pointer that we set with the setUserData()
	pongGame->draw();
}

//Via the Pong object (pongGame) we call its draw function to operate depending on the game state
void update(float ms) {
	Pong* pongGame = reinterpret_cast<Pong*>(getUserData());
	pongGame->update();
}

int main() {
	Pong pongGame;
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE); //Creating the window with given dimensions and a title
	setUserData(&pongGame); /*pongGame holds our app's state. A pointer of the Pong class is passed to this method.
							That pointer is useful for retrieving app data during callbacks for draw and update operations */
	setDrawFunction(draw); //All SGG draw functions are stored here in order to be used for the canvas drawing
	setUpdateFunction(update); //All SGG updated are stored here and is invoked whenever update events are triggered
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT); //Setting the canvas on which we will draw what we want.
	setCanvasScaleMode(CANVAS_SCALE_WINDOW); //The canvas is scaled to maximally fit the window with the same aspect ratio.
	startMessageLoop(); //All the window and UI events as well as the updates are processed here
	destroyWindow();
	return 0;
}
