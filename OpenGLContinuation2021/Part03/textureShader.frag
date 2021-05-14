#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main()
{
	// Output color = color of the texture at the specified UV
    vec4 colorRGBA = texture( myTextureSampler, UV );
	//set output - at the moment only rgb
	color = colorRGBA.rgb;
    //color = vec3(UV.x,UV.y,0.5);
}
