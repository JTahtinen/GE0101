#version 330 core

layout (location = 0) in vec2 position;

uniform vec2 u_Position;
uniform float u_ScreenRatio;

void main()
{
	gl_Position = vec4(u_Position.x, u_Position.y * u_ScreenRatio, 0, 1);
}