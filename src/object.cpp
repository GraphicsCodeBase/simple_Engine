#include "header/object.hpp"
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate, glm::perspective, glm::lookAt, etc.

//this is where i would define the functions in the object class of object.hpp.

object::object()
	: position(0.0f), scale(1.0f), rotation(0.0f),
	modelMatrix(1.0f), VAO(0), VBO(0), EBO(0),
	textureID(0), shaderProgram(0), indexCount(0)
{
	objName = "unnamed_object";

	// Optional debug output
	// std::cout << "Object created: " << objName << std::endl;
}


object::~object()
{
	// Delete GL resources if created
	if (VBO) glDeleteBuffers(1, &VBO);
	if (EBO) glDeleteBuffers(1, &EBO);
	if (VAO) glDeleteVertexArrays(1, &VAO);
	if (textureID) glDeleteTextures(1, &textureID);
}

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
mat4 object::getmodelMat()
{
	return modelMatrix;
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
	if (!glIsVertexArray(main_mesh.vao))
	{
		std::cerr << "Invalid VAO: " << main_mesh.vao << std::endl;
	}

	main_mesh.draw();
}

void object::renderObject()
{
	//render all the meshes in the object.
	for (auto& m : meshes)
	{
		m.bind();
		m.draw();
	}
}

void object::uploadMesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds)
{
	main_mesh = mesh::mesh(verts, inds);// Reconstructs and uploads new data
}


//add mesh into the container of meshes.
void object::addMesh(mesh InputMesh)
{
	meshes.push_back(std::move(InputMesh));
}
