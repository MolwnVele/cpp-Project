#pragma once
#ifndef _IMAGE
#define _IMAGE

#include "VecMath.h"
#include <iostream>

using namespace std;
using namespace math;
typedef Vec2<float> DuoFloater;

/*The "Image" class represents an image positioned in certain parts of the game.
  Since we are using a few images, it's best to encapsulate the idea here, despite not
  extending the GameObject class.*/
class Image {
private:
	DuoFloater imagePosition, imageDimensions; //2D Vector representations of the position and dimensions of the image
	string imageName; //name of the image
public:
	Image(const DuoFloater & imagePosition, const DuoFloater & imageDimensions, const string & imageName); //Constructor
	~Image(); //Destructor
	void drawImage(); //method to draw the image on the canvas
};

#endif