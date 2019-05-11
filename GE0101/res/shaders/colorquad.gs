#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 u_Dimensions;

in gl_Vertex
{
    vec4  gl_Position;
} gl_in[]; 

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	float halfX = u_Dimensions.x / 2.0f;
	float halfY = u_Dimensions.y / 2.0f;

	gl_Position = pos + vec4(-halfX, -halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(-halfX, halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(halfX, halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(halfX, -halfY, 0, 0);
	EmitVertex();
	EndPrimitive();
}