/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec3 VertexNormal;
layout (location = 3) in vec2 texture_coordinates;

uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform mat4 mvp;
uniform float time;
uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

out vec3 Position;
out vec3 Normal;
out vec2 tc;
out vec4 color2;

void main()
{
	Normal = normalize( normal_matrix * VertexNormal);
	Position = vec3( modelview_matrix * vec4(vertex_position,1.0) );
	tc = texture_coordinates;
	vec3 pos = vertex_position;
	gl_Position = mvp * vec4(pos, 1.0);
	color2 = vec4(red, green, blue, alpha);
}