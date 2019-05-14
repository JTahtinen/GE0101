#version 330 core

layout (location = 0) in vec2 position;

uniform vec2 u_Position;

void main()
{
	gl_Position = vec4(position.xy + u_Position.xy, 0, 1);
}