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

	proccessNode(scene->mRootNode, scene, tempObj);
	return tempObj;//return object.
}
//=====================
//	HELPER FUNCTIONS.
//=====================
void MeshLoader::proccessNode(aiNode* Node, const aiScene* scene, std::shared_ptr<object>& obj)
{
	//find out how many meshes is in the current Node.
	//for each node we proccess all the meshes.
	// Process only meshes attached to this node
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		unsigned int meshIndex = Node->mMeshes[i];
		mesh inMesh = proccessMesh(scene->mMeshes[meshIndex], scene);
		obj->addMesh(std::move(inMesh));
	}
	// **Recursive call for each child node**
	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		proccessNode(Node->mChildren[i], scene, obj);
	}
}

mesh MeshLoader::proccessMesh(aiMesh* aMesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32> indices;

	vertices.reserve(aMesh->mNumVertices);
	indices.reserve(aMesh->mNumFaces * 3); // assuming triangulated

	// 1. Loop through vertices and extract position only (for now)
	for (unsigned int i = 0; i < aMesh->mNumVertices; ++i)
	{
		Vertex vertex{};
		vertex.Position = {
			aMesh->mVertices[i].x,
			aMesh->mVertices[i].y,
			aMesh->mVertices[i].z
		};

		// Leave other vertex attributes (Normal, TexCoords, etc.) empty for now

		vertices.push_back(vertex);
	}

	// 2. Loop through faces and get indices
	for (unsigned int i = 0; i < aMesh->mNumFaces; ++i)
	{
		aiFace face = aMesh->mFaces[i];
		// Each face is a triangle because of aiProcess_Triangulate flag
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// 3. Create and return your mesh object with positions + indices
	return mesh(vertices, indices);
}
