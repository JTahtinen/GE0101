#version 330 core

layout (location = 0) in vec2 position;

uniform vec2 u_Position;
uniform vec2 u_Offset;
uniform vec2 u_Dimensions;
uniform float u_ScreenRatio;
uniform float u_Scale;

void main()
{
	//gl_Position = vec4(u_Position.x, u_Position.y * u_ScreenRatio, 0, 1) + vec4(u_Offset.x, (-u_Dimensions.y - u_Offset.y) * u_Scale * u_ScreenRatio, 0, 0);
	gl_Position = vec4(u_Position.x, u_Position.y * u_ScreenRatio, 0, 1) + vec4(u_Offset.x, -u_Offset.y * u_Scale * u_ScreenRatio, 0, 0);
	
	
}