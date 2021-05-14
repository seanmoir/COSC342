#version 330 core

// Ouput data
out vec3 color;
uniform vec4 colorValue;


void main()
{

	//color = colorValue.rgb;
	color = vec3(gl_FragCoord.r/1024, gl_FragCoord.g/768, 0.0);
    //color = vec3(1, 0, 0);

}
