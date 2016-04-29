/************************/
/** Second pass shader **/
/************************/

#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec2 UV;
out vec3 fragCoord;

void main(){
	gl_Position =  vec4(vertexPosition_modelspace,1);
	fragCoord = gl_Position.xyz;
	UV = (vertexPosition_modelspace.xy+vec2(1,1))/2.0;
	
}

