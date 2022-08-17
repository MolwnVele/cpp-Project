#include "ColorPicker.h"
#include <random>
#include <chrono>
#include "graphics.h"

using namespace graphics;

ColorPicker::ColorPicker(const DuoFloater& textPosition, float textSize, const string& text, const Color& color, const DuoFloater& buttonPosition, const DuoFloater& buttonDimensions) :
	textPosition(textPosition), textSize(textSize), text(text), GameObject(color), buttonPosition(buttonPosition), buttonDimensions(buttonDimensions) {}

ColorPicker::~ColorPicker() { cout << "Deleting ColorPicker object..." << endl;}

/*Checking if we pressed the button. By using the MouseState struct from the SGG library we can check whether the cursor
  is in the button area and whenever it is pressed a randomly generated color is set and a sound effect is also played*/
void ColorPicker::update() {
	MouseState MS;
	getMouseState(MS);
	//Checking if the cursor is within the button area with the checkBoundaries() method. The position of the cursor must be converted to canvas units
	bool inArea = checkBoundaries(buttonPosition, { window2CanvasX((float)MS.cur_pos_x) , window2CanvasY((float)MS.cur_pos_y) });
	if (inArea && MS.button_left_pressed) {
		setColor(generateRandomColor());
		playMusic(string(SOUNDS_PATH) + "select.wav", 0.85f, false);
	}
}

//Drawing the color button alongside its text, using the SGG library
void ColorPicker::draw() {
	Brush CPBrush;
	drawText(textPosition.x, textPosition.y, textSize, text, CPBrush);
	CPBrush.fill_color[0] = getColor().r;
	CPBrush.fill_color[1] = getColor().g;
	CPBrush.fill_color[2] = getColor().b;
	CPBrush.outline_opacity = 1.0f;
	CPBrush.outline_width = 2.5f;
	CPBrush.outline_color[0] = 0.5;
	CPBrush.outline_color[1] = 0.5;
	CPBrush.outline_color[2] = 0.5;
	drawRect(buttonPosition.x, buttonPosition.y, buttonDimensions.w, buttonDimensions.h, CPBrush);
}

/*Checking if the cursor position is within the button area.
Additional "correction" is required so that the button area is corresponding correctly to the cursor position
(For example, if we click just a tiny little bit outside the button it shouldn't change the color of the button*/
bool ColorPicker::checkBoundaries(const DuoFloater& buttonPosition, const DuoFloater& cursorPosition) {
	float minX = buttonPosition.x - buttonDimensions.w + 20.f;
	float maxX = buttonPosition.x + buttonDimensions.w - 20.f;
	float minY = buttonPosition.y - buttonDimensions.h + 20.f;
	float maxY = buttonPosition.y + buttonDimensions.h - 20.f;
	if ((cursorPosition.x >= minX && cursorPosition.x <= maxX) && (cursorPosition.y >= minY && cursorPosition.y <= maxY)) return true;
	else return false;
}

//Generating a "true" random color (RGB value) via Mersenne Twister 19937 generator.
Color ColorPicker::generateRandomColor() const {
	mt19937_64 RNG;
	//Random number generator initialization
	uint64_t timeSeed = chrono::high_resolution_clock::now().time_since_epoch().count(); //Time-dependent seed
	seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	RNG.seed(ss);
	uniform_real_distribution<float> U(0.f, 1.f); //initializing a uniform distribution in (0,1) - U ~ U(0,1)
	Color randomColor(-1.f);
	do {
		randomColor.r = U(RNG);
		randomColor.g = U(RNG);
		randomColor.b = U(RNG);
	} while (randomColor == Color(0.0f)); //Since the background, the black color must be avoided.
	return randomColor;
}