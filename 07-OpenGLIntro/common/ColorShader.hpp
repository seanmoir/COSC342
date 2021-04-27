#ifndef COLORSHADER_HPP
#define COLORSHADER_HPP

#include "Shader.hpp"
// Include standard headers
#include <string>
// Include GLEW
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ColorShader : public Shader 
{
public:
	ColorShader() {}
	ColorShader(glm::vec4 color)
	{
		Shader::Shader();
		setColor(color);
	}
	~ColorShader()
	{
		glDeleteProgram(Shader::programID);
	}

	void setColor(glm::vec4 color);

protected:
	glm::vec4 color;
};


#endif
