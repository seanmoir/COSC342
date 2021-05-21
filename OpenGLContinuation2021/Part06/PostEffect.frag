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

    //color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz ;
    

    bool sobel = false;
    
    if(!sobel){ //blur box
        float blurSizeH = 1.0/1024; 
        float blurSizeV = 1.0/768;
        
        vec3 result;
        for (int x = -4; x <= 4; x++){
            for (int y = -4; y <= 4; y++){
                vec2 tcord = vec2(UV.x + x * blurSizeH, UV.y + y * blurSizeV);
                result += texture(renderedTexture, tcord).xyz;
            }
        }
        // TODO: add all values up and devide by 9*9
        result = result / (9*9);
        color = result;
    }

    if(sobel){ //sobel
        vec2 targetSize;
        targetSize.x = 1024;
        targetSize.y = 768;

        vec4 top         = texture(renderedTexture, vec2(UV.x, UV.y+1.0/targetSize.y));
        vec4 bottom      = texture(renderedTexture, vec2(UV.x, UV.y-1.0/targetSize));
        vec4 left        = texture(renderedTexture, vec2(UV.x - 1.0 / targetSize.x, UV.y));
        vec4 right       = texture(renderedTexture, vec2(UV.x + 1.0 / targetSize.x, UV.y));
        vec4 topLeft     = texture(renderedTexture, vec2(UV.x - 1.0 / targetSize.x, UV.y + 1.0 / targetSize.y));
        vec4 topRight    = texture(renderedTexture, vec2(UV.x + 1.0 / targetSize.x, UV.y + 1.0 / targetSize.y));
        vec4 bottomLeft  = texture(renderedTexture, vec2(UV.x - 1.0 / targetSize.x, UV.y - 1.0 / targetSize.y));
        vec4 bottomRight = texture(renderedTexture, vec2(UV.x + 1.0 / targetSize.x, UV.y - 1.0 / targetSize.y));

	    
        vec4 sx = -topLeft - 2 * left - bottomLeft + topRight   + 2 * right  + bottomRight;
        vec4 sy = -topLeft - 2 * top  - topRight   + bottomLeft + 2 * bottom + bottomRight;

        vec4 result = sqrt(sx*sx+sy*sy);
        color = result.xyz;
    }  
    
}
