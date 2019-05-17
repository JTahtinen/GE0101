#version 330 core

layout (location = 0) in vec2 position;

uniform vec2 u_Position;
uniform vec2 u_Offset;
uniform vec2 u_Dimensions;


void main()
{
	float ratio = 9.0f / 16.0f;
	gl_Position = 0.2f * (vec4(u_Position.x * ratio, u_Position.y, 0, 1) + vec4(u_Offset.x * ratio, -u_Dimensions.y - u_Offset.y, 0, 0));
}