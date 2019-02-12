#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;


out vec4 v_color;
out vec2 v_texCoord;

uniform vec4 u_Color;

void main()
{
	gl_Position = vec4(position.xy, 1, 1);
	v_color = color + u_Color;
	v_texCoord = texCoord;
}