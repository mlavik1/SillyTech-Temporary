#region begin <ATTRIBUTES>

layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;
layout(location=2) in vec2 in_texcoord;

// Variables passed to geometry shader
smooth out vec4 v2f_positionW; // Position in world space.
smooth out vec4 v2f_normalW; // Surface normal in world space.
smooth out vec2 v2f_texcoord;

#region end



#region begin <UNIFORMS>

// Model, View, Projection matrix.
uniform mat4 ModelView;
uniform mat4 ProjectionView;
uniform mat4 CameraView;

#region end

#region begin <FUNCTIONS>

vec4 CalculateMVP()
{
	return ProjectionView*CameraView*ModelView * vec4(in_position, 1);
}

vec4 CalculatePosition()
{
	return ModelView * vec4(in_position, 1);
}

vec4 CalculateNormal()
{
	return transpose(inverse(ModelView)) * vec4(in_normal, 0);
}

vec2 CalculateTextureCoordinate()
{
	return in_texcoord;
}


#region end

    