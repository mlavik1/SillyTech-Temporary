/************************/
/** Second pass shader **/
/************************/
#version 330 core

// Texture coordinates
in vec2 UV;
in vec3 fragCoord;

// Output colour
out vec3 color;

// Texture(the scene, as seen from the current camera) - output of the first pass shaders
uniform sampler2D renderedTexture;
uniform float time;

uniform int invert; // TEST!!!
uniform int blackwhite; // TEST!!!
uniform int edge;
uniform int outline;


/***** Edge detection *****/
vec3 getEdge()
{
	vec3 col = vec3(0.0,0.0,0.0);
	mat3 sobelX = mat3(-1.0, -2.0, -1.0,
				   0.0,  0.0, 0.0,
				   1.0,  2.0,  1.0);
	mat3 sobelY = mat3(-1.0,  0.0,  1.0,
					   -2.0,  0.0, 2.0,
					   -1.0,  0.0,  1.0);  

	float sumX = 0.0;	// x-axis change
	float sumY = 0.0;	// y-axis change

	for(int i = -1; i <= 1; i++)
	{
		for(int j = -1; j <= 1; j++)
		{
			// texture coordinates should be between 0.0 and 1.0
			float x = UV.x + (float(i)/600.0);	
			float y =  UV.y + (float(j)/400.0);
			
			// Convolve kernels with image
			sumX += length(texture2D( renderedTexture, vec2(x, y) ).xyz) * float(sobelX[1+i][1+j]);
			sumY += length(texture2D( renderedTexture, vec2(x, y) ).xyz) * float(sobelY[1+i][1+j]);
		}
	}
	
	float g = abs(sumX) + abs(sumY);
	
	if(g > 1.0)
		col = vec3(1.0,1.0,1.0);
	
	return col;
}

/***** MAIN *****/
void main(){
		
	vec3 out_colour = texture2D(renderedTexture, UV).xyz;

	if(outline == 1)
	{
		vec3 edgecol = getEdge();
		if(edgecol != vec3(0.0,0.0,0.0))
				out_colour = vec3(0.0,0.0,0.0);
	}
	else if(edge==1) // edge detection
		out_colour = getEdge();;
	
		
	
	
	if(invert == 1) // invert colours
		out_colour.rgb = 1.0-out_colour.rgb;
	if(blackwhite == 1) // black & white
		out_colour.rgb = vec3(1.0,1.0,1.0)*length(out_colour.rgb);
		
	color = out_colour;
}
