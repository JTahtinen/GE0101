#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_Size;
layout (location = 2) in vec4 a_Color;

uniform float u_ScreenRatio;

out VS_OUT
{
	vec2 size;
	vec4 color;
} vs_out;


void main()
{
	gl_Position = vec4(a_Position.x, a_Position.y * u_ScreenRatio, 0, 1);
	vs_out.size = a_Size;
	vs_out.color = a_Color;
}