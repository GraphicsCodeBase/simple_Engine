#include "header/MeshLoader.hpp"
//=====================
//	MAIN PUBLIC FUNCTION.
//=====================
std::shared_ptr<object> MeshLoader::loadMesh(const std::string& filePath)
{
	//make an object
	auto tempObj = std::make_shared<object>();

	Assimp::Importer importer;//make an importer object.

	//read the file and define flags.
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//error checking.
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return tempObj; // return empty object
	}
}
//=====================
//	HELPER FUNCTIONS.
//=====================
void MeshLoader::proccessNode(aiNode* Node, const aiScene* scene, std::shared_ptr<object>& obj)
{


}

mesh MeshLoader::proccessMesh(aiMesh* Mesh, const aiScene* scene)
{
	return mesh();
}
