/******************************************************************************************************************
* Geometry shader 
**
* Calculates variables needed for wireframe rendering
* Using method described at: http://strattonbrazil.blogspot.no/2011/09/single-pass-wireframe-rendering_10.html
******************************************************************************************************************/



#version 330 core

// Input triangles
layout(triangles) in;
// Output triangles
layout(triangle_strip, max_vertices = 3) out;


//uniform vec4 EyePosW;   // Eye position in world space.

// Variables received from vertex shader
in vec4 v2f_positionW[]; // Position in world space.
in vec4 v2f_normalW[]; // Surface normal in world space.
in vec2 v2f_texcoord[];

// Variables passed on to fragment shader
out vec4 GNormal;
out vec4 GPosition;
out vec2 GTexCoord;
noperspective out vec3 GEdgeDistance;	// Distance to each of the three edges


// TODO: Receive viewport as uniform
const vec2 WIN_SCALE = vec2(1280.0, 640.0 );	// viewport of screen

void main()
{
	vec2 p0 = WIN_SCALE* gl_in[0].gl_Position.xy/gl_in[0].gl_Position.w;
	vec2 p1 = WIN_SCALE* gl_in[1].gl_Position.xy/gl_in[1].gl_Position.w;
	vec2 p2 = WIN_SCALE* gl_in[2].gl_Position.xy/gl_in[2].gl_Position.w;
	vec2 v0 = p2-p1;
	vec2 v1 = p2-p0;
	vec2 v2 = p1-p0;
	float area = abs(v1.x*v2.y - v1.y * v2.x);
	

	
	if(1==1)
	{
		// 1
		GEdgeDistance = vec3(area/length(v0),0,0);
		GPosition = v2f_positionW[0];
		GNormal = v2f_normalW[0];
		GTexCoord = v2f_texcoord[0];
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();
		// 2
		GEdgeDistance = vec3(0,area/length(v1),0);
		GPosition = v2f_positionW[1];
		GNormal = v2f_normalW[1];
		GTexCoord = v2f_texcoord[1];
		gl_Position = gl_in[1].gl_Position;
		EmitVertex();
		// 3
		GEdgeDistance = vec3(0,0,area/length(v2));
		GPosition = v2f_positionW[2];
		GNormal = v2f_normalW[2];
		GTexCoord = v2f_texcoord[2];
		gl_Position = gl_in[2].gl_Position;
		EmitVertex();
		
		// Finish
		EndPrimitive();
	}
	
}