#pragma once

class Utility
{
public:
	static void Log(const char* message);
	static void LogError(const char* message);
	static void LogWarning(const char* message);

	static void CalculateNormals(float* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, unsigned int vertexLength, unsigned int normalOffset);
};