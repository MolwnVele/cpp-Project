#include "Image.h"
#include "graphics.h"
#include "Initializer.h"

using namespace graphics;

Image::Image(const DuoFloater& imagePosition, const DuoFloater& imageDimensions, const string& imageName) :
	imagePosition(imagePosition), imageDimensions(imageDimensions), imageName(imageName) {}

Image::~Image() { cout << "Deleting Image Object..." << endl; }

//Drawing the image, using the SGG library
void Image::drawImage() {
	Brush imageBrush;
	imageBrush.texture = string(IMAGES_PATH) + imageName; //the texture will project the image we want and blend with the underlying color of the fill (here: white)
	imageBrush.outline_opacity = 0.0f;
	drawRect(imagePosition.x, imagePosition.y, imageDimensions.w, imageDimensions.h, imageBrush);
} 