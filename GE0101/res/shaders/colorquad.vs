#version 330 core

uniform vec2 u_Position;

void main()
{
	gl_Position = vec4(uPosition.xy, 0, 0);
}