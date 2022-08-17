#include "Net.h"
#include "graphics.h"
#include <iostream>

using namespace std;
using namespace graphics;

Net::Net(DuoFloater netDimensions, Color netColor) : netDimensions(netDimensions), GameObject(netColor){}

Net::~Net() { cout << "Deleting Net object..." << endl; }

void Net::update() {}

void Net::draw() {
	Brush netBrush;
	netBrush.outline_color[0] = getColor().r;
	netBrush.outline_color[1] = getColor().g;
	netBrush.outline_color[2] = getColor().b;
	//"Formula" to create a vertical dotted line representing the net
	//windowWidth/2 is the midpoint and each "sub-line" of the dotted line has length of 5 pixels.
	//Modulo 8 is a decent number to use for the "slicing".
	for (int y = 0; y < netDimensions.h; ++y) {
		if (!(y % 8)) {
			drawLine(netDimensions.w / 2.0f, (float)y, netDimensions.w / 2.0f, (float)(y + 5), netBrush);
		}
	}
}