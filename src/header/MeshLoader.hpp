#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "object.hpp"
#include "mesh.hpp"
//this would be helper functions that 
// will load in the meshes from assimp.
class MeshLoader
{
	//load object from a file path and returns an object
	//to be rendered.
public:
	std::shared_ptr<object> loadMesh(const std::string& filePath);
private:
	//helper functions.
	void proccessNode(aiNode* Node, const aiScene* scene, std::shared_ptr<object>& obj);//proccessing node
	mesh proccessMesh(aiMesh* Mesh, const aiScene* scene);//proccessing Mesh.

};