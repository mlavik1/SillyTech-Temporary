#region begin <INCLUDES>
#include <Lights.fxh>
#region end


#region begin <FUNCTIONS>

vec3 CalculatePhong(vec3 diffuseColour, vec3 specularColour)
{
	vec3 light_contribution = vec3(0.0,0.0,0.0);
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
		vec3 diffuseContribution = max(dot(N,L),0.0) * lights[i].diffuseColour * diffuseColour;
		vec3 specularContribution = pow(RdotV, 32) * lights[i].specularColour * specularColour;
		light_contribution = (ambientContribution+diffuseContribution+specularContribution);
	}
	
	return = light_contribution;
}

#region end