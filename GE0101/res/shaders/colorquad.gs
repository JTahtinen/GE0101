#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 u_Dimensions;

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	float halfX = u_Dimensions.x / 2.0;
	float halfY = u_Dimensions.y / 2.0;

	gl_Position = pos + vec4(-halfX, -halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(-halfX, halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(halfX, -halfY, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(halfX, halfY, 0, 0);
	EmitVertex();
	EndPrimitive();
}