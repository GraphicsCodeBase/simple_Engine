#include "header/object.hpp"
//this is where i would define the functions in the object class of object.hpp.

//setting position
void object::setPosition(const vec3& pos)
{
	position = pos;
}
//setting scale.
void object::setScale(const vec3& scl)
{
	scale = scl;
}
//setting rotation.
void object::setRotation(const vec3& rot)
{
	rotation = rot;
}

vec3 object::getPos()
{
	return position;
}

vec3 object::getScl()
{
	return scale;
}

vec3 object::getRot()
{
	return rotation;
}
