
#include "MTLShader.hpp"
// complete the setters with the appropriate method for passing information to the shaders


MTLShader::MTLShader(){
        
}

// version of constructor that allows for  vertex and fragment shader with differnt names
    
MTLShader::MTLShader(std::string vertexshaderName, std::string fragmentshaderName): Shader(vertexshaderName, fragmentshaderName){
    
    setUpShaderParameters();
    
}

// version of constructor that assumes that vertex and fragment shader have same name
MTLShader::MTLShader(std::string shaderName): Shader(shaderName){
    
    setUpShaderParameters();
    
}

MTLShader::~MTLShader(){
    glDeleteTextures(1, &m_TextureID);

}

//Sets a default diffuse color of white and sets the texture to NULL
void MTLShader::setUpShaderParameters(){
    m_diffuseColor = glm::vec4(1.0);
    GLint diffusecolorID = glGetUniformLocation(programID, "diffuseColor");
    glProgramUniform4fv(programID, diffusecolorID, 1, &m_diffuseColor[0]);

    m_texture =NULL;
    m_TextureID = glGetUniformLocation(programID, "myTextureSampler");
}

//sets the texture for the bind function to refernce when bidnging the texture to the shader
void MTLShader::setTexture(Texture* texture){
    m_texture = texture;
}

//sets the light postion and creates a uniform to pass the light position to the GPU
void MTLShader::setLightPos(glm::vec3 lightPos){
    m_lightPos = lightPos;
    m_lightPosID = glGetUniformLocation(programID, "lightPosWorldspace");
    glUniform3f(m_lightPosID, m_lightPos.x, m_lightPos.y, m_lightPos.z);
}

//sets the diffuse color and creates a uniform to pass the color to the GPU
void MTLShader::setDiffuse(glm::vec3 diffuse){
    
    m_diffuseColor= glm::vec4(diffuse[0],diffuse[1],diffuse[2], 1);
    GLint diffusecolorID = glGetUniformLocation(programID, "diffuseColor");
    glProgramUniform4fv(programID,diffusecolorID,1, &m_diffuseColor[0]);
}

//sets the ambient color and creates a uniform to pass the color to the GPU
void MTLShader::setAmbient(glm::vec3 ambient){
    
    m_ambientColor= glm::vec4(ambient[0],ambient[1],ambient[2], 1);
    GLint ambientcolorID = glGetUniformLocation(programID, "ambientColor");
    glProgramUniform4fv(programID,ambientcolorID,1, &m_ambientColor[0]);
	
}

//sets the specular color and creates a uniform to pass the color to the GPU
void MTLShader::setSpecular(glm::vec3 specular){
    
    m_specularColor= glm::vec4(specular[0],specular[1],specular[2], 1);
    GLint specularcolorID = glGetUniformLocation(programID, "specularColor");
    glProgramUniform4fv(programID,specularcolorID,1, &m_specularColor[0]);
	
}

//sets the opacity and creates a uniform to pass the opacity to the GPU
void MTLShader::setOpacity(float opacity){
    m_opacity= opacity;
    GLint opacityID = glGetUniformLocation(programID, "opacity");
    glProgramUniform1fv(programID, opacityID, 1, &m_opacity);
}

//sets the specular exponent and creates a uniform to pass the exponent to the GPU
void MTLShader::setSpecularExponent(float ns) {
    m_ns = ns;
    GLint nsID = glGetUniformLocation(programID, "ns");
    glProgramUniform1fv(programID, nsID, 1, &m_ns);
}

void MTLShader::setRenderMode(float renderMode){
    m_renderMode= renderMode;

}


void MTLShader::bind(){
    // Use our shader
    glUseProgram(programID);
    // Bind our texture in Texture Unit 0
    if(m_texture!=NULL){
        m_texture->bindTexture();
        // Set our "myTextureSampler" sampler to user Texture Unit 0 using glUniform1i
		
    }
    
}
