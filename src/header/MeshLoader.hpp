#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "object.hpp"
//this would be helper functions that 
// will load in the meshes from assimp.
class MeshLoader
{
	//load object from a file path and returns an object
	//to be rendered.
	object loadMesh(const std::string& filePath);


};