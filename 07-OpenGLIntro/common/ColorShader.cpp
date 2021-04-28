#include "ColorShader.hpp"

ColorShader::ColorShader() {}

ColorShader::ColorShader(glm::vec4 color)
{
		initShaders("colorShader.vert", "colorShader.frag");
		setColor(color);
}

ColorShader::~ColorShader()
{
	glDeleteProgram(programID);
}

void ColorShader::setColor(glm::vec4 color)
{
	GLint colorID = glGetUniformLocation(programID, "colorValue");
	glProgramUniform4fv(programID, colorID, 1, &color[0]);
}