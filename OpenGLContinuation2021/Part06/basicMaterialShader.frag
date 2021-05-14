#version 330 core
//Phong shading model
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 posWorldspace;
in vec3 normalCameraspace; //normal in camera space
in vec3 eyeDirectionCameraspace; // eye direction in camera space
in vec3 lightDirectionCameraspace; // light direction in camera space

// Ouput data
layout(location = 0) out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 lightPosWorldspace;
const float shininess = 30.0;

void main(){
    
    // Light emission properties
    vec3 lightColor = vec3(1,1,1);
    
    // Material properties
    vec3 textureVal = texture( myTextureSampler, UV ).rgb;
    vec3 ambientMatColor = vec3(0.1,0.1,0.1);
    vec3 specularMatColor = vec3(0.3,0.3,0.3);
    
    // Distance to the light
    float distance = length( lightPosWorldspace - posWorldspace );
    
    // Normal of the computed fragment, in camera space
    vec3 n = normalize( normalCameraspace );
    // Direction of the light (from the fragment to the light)
    vec3 l = normalize( lightDirectionCameraspace );
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cosTheta = clamp( dot( n,l ), 0,1 );
    
    // Eye vector (towards the camera)
    vec3 E = normalize(eyeDirectionCameraspace);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l,n);
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    
    vec3 diffuseComponent = textureVal * lightColor * cosTheta;
    vec3 ambientComponent = ambientMatColor *textureVal; // we use the same texture for the ambient component
    vec3 specularComponent = specularMatColor * lightColor  * pow(cosAlpha,shininess/4.0);
    
    color =
    // Ambient : simulates indirect lighting
    ambientComponent +
    // Diffuse : "color" of the object
    diffuseComponent +
    // Specular : reflective highlight, like a mirror
    specularComponent;
    
    
    
}
