#version 140

uniform vec3 lightdir;
uniform vec3 color;

// Output color
out vec4 fragcolor;

// Variables from vertex to fragment shader
in vec3 _normal; //normal vector


void main()
{
	float diffuse = clamp(dot(lightdir, _normal), 0.0, 1.0);
	fragcolor = vec4(color * (diffuse + 0.1), 1.0);
}
