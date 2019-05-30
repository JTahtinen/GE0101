#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;


out vec4 v_color;
out vec2 v_texCoord;

uniform vec4 u_Color;
uniform vec4 u_Offset;
uniform float u_ScrRatio;
uniform float u_Scale;

void main()
{
	gl_Position = vec4(u_Offset.x / u_Offset.z, u_Offset.y * u_ScrRatio / u_Offset.z, 0, 0) + vec4(position.x / u_Offset.z * u_Scale, position.y / u_Offset.z * u_Scale * u_ScrRatio, 0, 1);
	v_color = u_Color;
	v_texCoord = texCoord;
}