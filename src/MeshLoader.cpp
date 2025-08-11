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
	//find out how many meshes is in the current Node.
	//for each node we proccess all the meshes.
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		unsigned int meshIndex = Node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[meshIndex];
		proccessMesh(mesh, scene);//helper function to procces mesh.
	}
}

mesh MeshLoader::proccessMesh(aiMesh* Mesh, const aiScene* scene)
{
	std::vector<vec3> vertices;
	std::vector<uint32> indices;
	//basic idea for each mesh i would make an 
	//object instance using the object class.


	//loop through all the vertices.




	//loop over the faces (trianles.)


	//return mesh.
}
