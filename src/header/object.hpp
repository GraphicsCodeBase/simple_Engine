#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <glad/glad.h>
#include <vector>
#include "mesh.hpp"
using namespace glm;

class object
{
	public:
		object();//basic constructor.
		~object();//clean up destructor.


		//basic getters and setters
		void setPosition(const vec3& pos);
		void setScale(const vec3& scl);
		void setRotation(const float& rot); // Euler angles for now
		vec3 getPos(); //get position
		vec3 getScl(); //get scale
		float getRot(); //get rotation.
		mat4 getmodelMat();
		//update model matrix 
		void updateModelMatrix();
		//to be implemented soon.
		void update(float dt);
		void render();

		//create mesh
		void uploadMesh(const std::vector<glm::vec3>& verts, const std::vector<uint32_t>& inds);

	private:

		std::string objName;//string name for ID purporses.

		//model attributes.
		vec3 position;
		vec3 scale;
		float rotation;
		//model Matrix.
		mat4 modelMatrix;

		//graphics attributes.
		GLuint VAO, VBO, EBO;
		GLuint textureID;
		GLuint shaderProgram;
		size_t indexCount;
		//mesh
		mesh main_mesh;
};