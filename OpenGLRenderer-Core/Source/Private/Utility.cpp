#include "Utility.h"

#include "glm/glm.hpp"

void Utility::CalculateNormals(float* vertices, unsigned int numVertices, unsigned int* indices,
	unsigned int numIndices, unsigned int vertexLength, unsigned int normalOffset)
{
	/* Loop through each triangle */
	for (unsigned int i = 0; i < numIndices; i += 3)
	{
		/* Get the indices of the triangle */
		unsigned int index0 = indices[i] * vertexLength;
		unsigned int index1 = indices[i + 1] * vertexLength;
		unsigned int index2 = indices[i + 2] * vertexLength;

		/* Get the vectors of the triangle */
		glm::vec3 v1(vertices[index1] - vertices[index0], vertices[index1 + 1] - vertices[index0 + 1], vertices[index1 + 2] - vertices[index0 + 2]);
		glm::vec3 v2(vertices[index2] - vertices[index0], vertices[index2 + 1] - vertices[index0 + 1], vertices[index2 + 2] - vertices[index0 + 2]);

		/* Calculate the normal */
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		/* Add the normal to the vertices */
		vertices[index0 + normalOffset] += normal.x;
		vertices[index0 + normalOffset + 1] += normal.y;
		vertices[index0 + normalOffset + 2] += normal.z;

		vertices[index1 + normalOffset] += normal.x;
		vertices[index1 + normalOffset + 1] += normal.y;
		vertices[index1 + normalOffset + 2] += normal.z;

		vertices[index2 + normalOffset] += normal.x;
		vertices[index2 + normalOffset + 1] += normal.y;
		vertices[index2 + normalOffset + 2] += normal.z;
	}


	/* Normalize the normals */
	for (unsigned int i = 0; i < numVertices; i += vertexLength)
	{
		glm::vec3 normal(vertices[i + normalOffset], vertices[i + normalOffset + 1], vertices[i + normalOffset + 2]);
		normal = glm::normalize(normal);

		vertices[i + normalOffset] = normal.x;
		vertices[i + normalOffset + 1] = normal.y;
		vertices[i + normalOffset + 2] = normal.z;
	}
}
