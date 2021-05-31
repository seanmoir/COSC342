#version 330 core

// Interpolated values from the vertex shaders
// e.g.
in vec2 UV;
in vec3 posWorldspace;
in vec3 normalCameraspace; //normal in camera space
in vec3 eyeDirectionCameraspace; // eye direction in camera space
in vec3 lightDirectionCameraspace; 

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform vec3 lightPosWorldspace;
uniform sampler2D myTextureSampler;
uniform float opacity;
uniform float ns;

void main(){
	
	// Material properties
	//TODO: compute light model here
    //color.rgb = diffuseColor.rgb;
    //color.a = 1.0;



    	
	// Material properties
	vec3 textureVal = texture( myTextureSampler, UV ).rgb;  //texture map will be used for diffuse and ambient texture map
	
	// Distance to the light we could use this to diminish the amount of light the further away but we do not for simplification
	float distance = length( lightPosWorldspace - posWorldspace );
	
	// We now work in camera space
	// Normal of the computed fragment, in camera space
	vec3 N = normalize( normalCameraspace );
	// Direction of the light (from the fragment to the light) in camera space
	vec3 L = normalize( lightDirectionCameraspace );
	
	// We use the cosine of the angle theta between the normal and the light direction to compute the diffuse component.
	// The cosine is clamped to contrain it between 0 and 1
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( N,L), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(eyeDirectionCameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-L,N);

	//BLINN-PHONG RELFECTION MODEL
	vec3 H = L + E;
	
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// The cosine is clamped to contrain it between 0 and 1 to avoid negative values
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1

	//PHONG
	//float cosAlpha = clamp( dot( E,R ), 0,1 );

	//BLINN-PHONG
	float cosAlpha = clamp( dot( H,normalCameraspace ), 0,1 );

    vec3 diffuseComponent = diffuseColor.rgb * textureVal * cosTheta;
	vec3 ambientComponent = ambientColor.rgb * textureVal; //for simplification we reuse the diffuse texture map for the ambient texture map
    vec3 specularComponent = specularColor.rgb * pow(cosAlpha,ns);
    
	color.rgb =
	// Ambient : simulates indirect lighting
	ambientComponent + 
	// Diffuse : "color" of the object
	diffuseComponent +
	// Specular : reflective highlight, like a mirror
	specularComponent;
    
	color.a = opacity;
}
