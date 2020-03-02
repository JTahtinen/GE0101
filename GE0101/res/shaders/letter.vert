
#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_Dimensions;
layout (location = 2) in vec2 a_Offset;
layout (location = 3) in vec2 a_TexCoord;

uniform float u_ScreenRatio;
uniform float u_Scale;
uniform float u_Base;

out VS_OUT
{
	vec2 dimensions;
	vec2 texCoord;
} vs_out;

void main()
{
	//gl_Position = vec4(a_Position.x + a_Offset.x, u_Base * u_ScreenRatio + a_Position.y - (a_Offset.y + a_Dimensions.y) * u_Scale * u_ScreenRatio, 0, 1);
	
	gl_Position = vec4(a_Position.x + a_Offset.x, (a_Position.y + u_Base ) * u_ScreenRatio - (a_Offset.y + a_Dimensions.y) * u_Scale * u_ScreenRatio, 0, 1);
	vs_out.dimensions = a_Dimensions;
	vs_out.texCoord = a_TexCoord;
}