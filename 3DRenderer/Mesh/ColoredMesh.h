#pragma once

#include "BasicMesh.h"

class ColoredMesh : public BasicMesh
{
public:
	ColoredMesh(const Shader& shader);
	virtual ~ColoredMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals, const std::vector<GLfloat>& verticesColorBuffer);
	void clearMesh();

	virtual void render(const UniformLocations& uniformLocations) const override;

private:
	void bindBuffers(const std::vector<GLfloat>& verticesColorBuffer);

	GLuint verticesColorBuffer;
};

