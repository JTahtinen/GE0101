#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Offset;

uniform float u_ScrRatio;

void main()
{
	gl_Position = vec4((a_Position.x + a_Offset.x) * 0.3, (a_Position.y + a_Offset.y) * 0.3 * u_ScrRatio, 0, 1.0);
}