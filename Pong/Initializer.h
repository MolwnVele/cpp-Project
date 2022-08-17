#pragma once

//Macros as constant values for usage when necessary.
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Pong"
#define CANVAS_WIDTH 1260
#define CANVAS_HEIGHT 710
#define BALL_WIDTH 7
#define BALL_HEIGHT 7
#define PADDLE_WIDTH 7
#define PADDLE_HEIGHT 50
#define FONTS_PATH "assets/fonts/"
#define SOUNDS_PATH "assets/sounds/"
#define IMAGES_PATH "assets/images/"

//An enumeration representing the different types of collisions in the game, with the "Collision" alias.
typedef enum collisionType {
	None,
	Top,
	Middle,
	Bottom,
	Left,
	Right
} Collision;

//An enumeration representing the game states, with the "GameStatus" alias.
typedef enum gameState {
	STATUS_START,
	STATUS_PLAYING,
	STATUS_PAUSE,
	STATUS_END
} GameStatus;