/*#include "graphics.h"
#include "Initializer.h"
#include "Game.h"

using namespace std;
using namespace graphics;

void update(float ms) {
	Game* pongGame = reinterpret_cast<Game*>(getUserData());
	pongGame->update();
}

void draw() {
	Game* pongGame = reinterpret_cast<Game*>(getUserData());
	pongGame->draw();
}

int main() {
	Game pongGame;
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	setUserData(&pongGame);
	setDrawFunction(draw);
	setUpdateFunction(update);
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	pongGame.init();
	startMessageLoop();
	//destroyWindow();
	return 0;
}*/