#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>
#include <glm.hpp>

class MeshData
{
public:
	MeshData();
	~MeshData();

public:
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mNormals;
	std::vector<glm::vec2> mTexCoords;
	std::vector<unsigned int> mIndices;
};


#endif