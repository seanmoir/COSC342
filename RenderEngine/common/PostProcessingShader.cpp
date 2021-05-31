
#include "PostProcessingShader.hpp"

PostProcessingShader::PostProcessingShader(){
        
}
// version of constructor that allows for  vertex and fragment shader with differnt names

PostProcessingShader::PostProcessingShader(std::string vertexshaderName, std::string fragmentshaderName): Shader(vertexshaderName, fragmentshaderName){
    
    timeID = glGetUniformLocation(programID, "time");
    m_TextureID = glGetUniformLocation(programID, "renderedTexture");
    
}

// version of constructor that assumes that vertex and fragment shader have same name
PostProcessingShader::PostProcessingShader(std::string shaderName): Shader(shaderName){
    
    timeID = glGetUniformLocation(programID, "time");
    m_TextureID = glGetUniformLocation(programID, "renderedTexture");
    
}

PostProcessingShader::~PostProcessingShader(){
    
}

void PostProcessingShader::setTime(float t){
    glUniform1f(timeID, (float)(t) );
    
}

void PostProcessingShader::bindTexture(){
     // Set our "myTextureSampler" sampler to user Texture Unit 0
     glUniform1i(m_TextureID, 0);
 }

void PostProcessingShader::bindShader(){
    
    // Use our shader
    glUseProgram(programID);
    // Bind our texture in Texture Unit 0
    
    
}

//sets the render mode for the application and passes it on to the GPU via a uniform variable,
//this will set if and what special effect is active
void PostProcessingShader::setRenderMode(float renderMode){
    m_render_mode = renderMode;
    render_modeID = glGetUniformLocation(programID, "render_mode");
    glProgramUniform1iv(programID, render_modeID, 1, &m_render_mode);
 
}
