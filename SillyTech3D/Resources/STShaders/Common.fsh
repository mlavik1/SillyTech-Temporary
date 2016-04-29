#region begin <ATTRIBUTES>

smooth in vec4 GPosition;	// Position in world space.
smooth in vec4 GNormal;	// Surface normal in world space.
smooth in vec2 GTexCoord;

#region end



#region begin <UNIFORMS>

// Distance to all three edges
noperspective in vec3 GEdgeDistance;
uniform vec3 EyePosW;   // Eye position in world space.
uniform sampler2D sampler;

#region end