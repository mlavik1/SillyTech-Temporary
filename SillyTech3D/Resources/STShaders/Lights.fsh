#region begin <STRUCTURES>

struct LightSource
{
	vec3 position;
	vec3 direction;
	vec3 ambientColour;
	vec3 diffuseColour;
	vec3 specularColour;
	int type;
};

#region end



#region begin <UNIFORMS>

uniform LightSource lights[MAX_NUM_LIGHTS];
uniform int numLights;

#region end