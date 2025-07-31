#include "header/object.hpp"
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate, glm::perspective, glm::lookAt, etc.

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
//setting rotation.(using float)
void object::setRotation(const float& rot)
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

float object::getRot()
{
	return rotation;
}
//create the model matrix 
void object::updateModelMatrix()
{
	// Start with identity
	glm::mat4 model = glm::mat4(1.0f);

	// Apply transformations: scale → rotate → translate
	model = glm::translate(model, position);

	// If you're using just one float rotation angle (e.g., Y-axis rotation):
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, scale);

	modelMatrix = model;
}

void object::update(float dt)
{
	//update object.
	rotation += dt; // simple spin over time (if `rotation` is a float)
	updateModelMatrix(); // rebuild matrix based on updated values
}

void object::render()
{
	mesh.draw();
}

void object::uploadMesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds)
{
	mesh = mesh::mesh(verts, inds);// Reconstructs and uploads new data
}
