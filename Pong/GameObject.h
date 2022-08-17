#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include "VecMath.h"

using namespace math;
typedef Vec2<float> DuoFloater; //an alias representing a 2D vector of float values
typedef Vec3<float> Color; //an alias representing the color of a component (3D Vector of floats)

//The GameObject abstract class represents a component that will be used to create the game. For example, the Ball is a game object that can be drawn and updated depending on the situation.
class GameObject {
private:
	Color color = { 1.0f }; //data member, as every game object (any class that extends GameObject) has a color.
public:
	//Constructors
	GameObject() {}
	GameObject(const Color & color) : color(color) {}
	//Destructor
	virtual ~GameObject() {}
	//Pure virtual functions. Every GameObject must implement these and in the declaration we use the "override" specifier
	virtual void draw() = 0;
	virtual void update() = 0;
	//Getter & Setter
	const Color getColor() const { return color; }
	void setColor(const Color & color) { this->color = color; }
};
#endif