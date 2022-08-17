#include "graphics.h"
using namespace graphics;

#ifndef _ASSET
#define _ASSET

class Asset {
public:
	virtual void update(float ms);
	virtual void draw();
	virtual ~Asset();
};
#endif