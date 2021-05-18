#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;
....blurSizeH = 1 / 1024;
....blurSizeV = 1 / 80;
vec2 boxBlur(vec2 UV){
	
	for (int x = -4; x <= 4; x++)
	for (int y = -4; y <= 4; y++)
	vec4 sum += texture(vec4(UV.x + x * blurSizeH, UV.y + y * blurSizeV)/81);
	
	return sum;
}
void main(){
	color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz ;
    
}
