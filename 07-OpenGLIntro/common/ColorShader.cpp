#include "ColorShader.hpp"

void ColorShader::setColor(glm::vec4 color)
{
	GLint colorID = glGetUniformLocation(Shader::programID, "colorValue");
	glProgramUniform4fv(programID, colorID, 1, &color[0]);
}