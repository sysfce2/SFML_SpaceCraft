#include "Orbit.h"

Orbit::Orbit(size_t maxSize, const glm::vec3 orbitColor, std::shared_ptr<ShaderManager> shaderManager)
	: CircularVector(maxSize)
	, Renderable(shaderManager)
	, color(orbitColor)
	, VAO(0)
	, VBO(0)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Orbit::~Orbit()
{
	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

void Orbit::addPoint(const glm::vec3& point)
{
	CircularVector::push(point);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, CircularVector::getActualSize() * sizeof(glm::vec3), CircularVector::getData(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Orbit::render(std::shared_ptr<SceneContext> sceneContext) const
{
	auto shader = shaderManager->getShader("orbitShader");
	auto& uniforms = shader->getUniformLocations();

	if (shader != shaderManager->getLastUsedShader())
	{
		shader->useShader();
		shaderManager->setLastUsedShader(shader);
	}

	sceneContext->cameraManager->useCamera(uniforms.uniformView, uniforms.uniformCameraPosition, uniforms.uniformProjection);
	glUniform3f(uniforms.uniformOrbitColor, color.r, color.g, color.b);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(CircularVector::getActualSize()));
	glBindVertexArray(0);
}
