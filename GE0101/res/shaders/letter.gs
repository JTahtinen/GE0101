#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 u_Dimensions;
uniform vec2 u_Offset;
uniform vec2 u_TexCoord;
uniform float u_ScreenRatio;
uniform float u_Scale;

out vec2 v_TexCoord;

void main()
{	
	vec2 dimensions = vec2(u_Dimensions.x * u_Scale, u_Dimensions.y * u_Scale * u_ScreenRatio);
	vec4 pos = gl_in[0].gl_Position;
	gl_Position = pos;
	v_TexCoord = u_TexCoord + vec2(0, u_Dimensions.y);
	EmitVertex();
	gl_Position = pos + vec4(0, dimensions.y, 0, 0);
	v_TexCoord = u_TexCoord;
	EmitVertex();
	gl_Position = pos + vec4(dimensions.x, 0, 0, 0) ;
	v_TexCoord = u_TexCoord + u_Dimensions;
	EmitVertex();
	gl_Position = pos + vec4(dimensions.x, dimensions.y, 0, 0);
	v_TexCoord = u_TexCoord + vec2(u_Dimensions.x, 0);
	EmitVertex();
	EndPrimitive();
}