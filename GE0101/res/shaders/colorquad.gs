#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 u_Dimensions;
uniform float u_ScreenRatio;

void main()
{
	vec4 pos = gl_in[0].gl_Position;

	gl_Position = pos;
	EmitVertex();
	gl_Position = pos + vec4(0, -u_Dimensions.y * u_ScreenRatio, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(u_Dimensions.x, 0, 0, 0);
	EmitVertex();
	gl_Position = pos + vec4(u_Dimensions.x, -u_Dimensions.y * u_ScreenRatio, 0, 0);
	EmitVertex();
	EndPrimitive();
}