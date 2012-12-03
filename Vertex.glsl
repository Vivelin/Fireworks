#version 140

uniform mat4 matmodelview;
uniform mat4 matprojection;

in vec4 in_position;
in vec3 in_normal;

// End of header part

// Variables from vertex to fragment shader
out vec3 _normal;


void main()
{
	// Get a copy of the normal vector and texcoord
	_normal = (matmodelview * vec4(in_normal, 0.0)).xyz;
	
	// Transform the vertex position to screencoordinates
	gl_Position = matprojection * (matmodelview * in_position);
}
