#pragma once

#ifndef _COLORPICKER
#define _COLORPICKER

#include "GameObject.h"
#include "Initializer.h"
#include <iostream>

using namespace math;
using namespace std;

/*The "ColorPicker" class is a GameObject which represents a button with a text to the right of it.
  It allows changes to different game components, depending on what we chose to change.*/
class ColorPicker : public GameObject {
private:
	DuoFloater textPosition, buttonPosition, buttonDimensions; //2D vector representations of the text position as well the button position and its dimensions
	float textSize;
	string text;
	unsigned int windowWidth = WINDOW_WIDTH, windowHeight = WINDOW_HEIGHT;
public:
	ColorPicker(const DuoFloater & textPosition, float textSize, const string & text, const Color & color, const DuoFloater & buttonPosition, const DuoFloater & buttonDimensions); //Constructor
	~ColorPicker(); //Destructor

	//Pure virtual function overriden for implementation
	void update() override;
	void draw() override;

	//Getters
	Color getCPColor() const { return getColor(); }
	DuoFloater getButtonPosition() const { return buttonPosition; }
	DuoFloater getButtonDimensions() const { return buttonDimensions; }

	//Converting window units to canvas units
	float window2CanvasX(float x) { return x * CANVAS_WIDTH / (float)windowWidth;}
	float window2CanvasY(float y) { return y * CANVAS_HEIGHT / (float)windowHeight;}

	bool checkBoundaries( const DuoFloater & buttonPosition, const DuoFloater & cursorPosition); //method to check whether we press the button or not
	Color generateRandomColor() const; //generate a random color for a broad color palette.


};

#endif