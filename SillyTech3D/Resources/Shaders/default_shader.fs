#version 330 core

#define MAX_NUM_LIGHTS		10

#define DIRECTIONAL_LIGHT	1
#define POINT_LIGHT			2
#define SPOT_LIGHT			3




struct LightSource
{
	vec3 position;
	vec3 direction;
	vec3 ambientColour;
	vec3 diffuseColour;
	vec3 specularColour;
	int type;
};

/*** Attributes ***/
smooth in vec4 GPosition;	// Position in world space.
smooth in vec4 GNormal;	// Surface normal in world space.
smooth in vec2 GTexCoord;

/*** Uniforms ***/
// Distance to all three edges
noperspective in vec3 GEdgeDistance;
uniform vec3 EyePosW;   // Eye position in world space.
uniform sampler2D sampler;

uniform LightSource lights[MAX_NUM_LIGHTS];
uniform int numLights;

uniform vec4 diffuse_colour;

uniform int test;
uniform int wireframe;
uniform int nomesh;
uniform int use_colour;
uniform int no_lighting;

//layout (std140) uniform Test {
//    vec4 diffuse;
//    vec4 ambient;
//};


/*** Output ***/
layout (location=0) out vec4 out_color;


/***** MAIN *****/
void main()
{
	vec4 baseColour = vec4(0.0,0.0,0.0,1.0);
	
	vec2 texCoord = GTexCoord;
	texCoord.y  = (texCoord.y-0.5)*-1.0+ 0.5;
	
	
		
	//out_color.xyz = texture( sampler, texCoord ).xyz*texture( sampler, texCoord ).a;
	//out_color = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
	if(use_colour == 1)
		baseColour = diffuse_colour;
	else
		baseColour = texture( sampler, texCoord );
	
	vec3 light_contribution = baseColour.xyz;
	for(int i = 0; i < numLights && i < MAX_NUM_LIGHTS; i++)
	{
		if(no_lighting == 1)
			break;
		vec3 N = normalize(GNormal.xyz);
		vec3 L = normalize(lights[i].position - N);
		vec3 V = normalize(EyePosW-GPosition.xyz);
		vec3 R = normalize(reflect( -L, N ));
		float RdotV = max( dot( R, V ), 0.0 );
		//out_color.xyz = vec3(1,0,0)*RdotV;
		vec3 ambientContribution = lights[i].ambientColour * baseColour.xyz;
		vec3 diffuseContribution = max(dot(N,L),0.0) * lights[i].diffuseColour * baseColour.xyz;
		vec3 specularContribution = pow(RdotV, 32) * lights[i].specularColour * baseColour.xyz;
		light_contribution = (ambientContribution+diffuseContribution+specularContribution);
		//light_contribution = N *vec3(1,0,0);
	}
	
	out_color.xyz = light_contribution;
	out_color.a = baseColour.w;
	
	/*** WIREFRAME ***/
	if(wireframe == 1) {
		// determine distance to closest edge
		float nearD = min(min(GEdgeDistance[0],GEdgeDistance[1]),GEdgeDistance[2]);
		float edgeIntensity = exp2(-1.0*nearD*nearD);	
		out_color.xyz = edgeIntensity * vec3(1,0,0) + out_color.xyz;
		
		if(nomesh == 1 && edgeIntensity < 0.1)
		{
			out_color.a = 0.0;
		}
	}
	
	
	if(test == 1)
		out_color.xyz = normalize(GNormal.xyz);
	
	//out_color = diffuse;
	
}