#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 u_Dimensions;
uniform vec2 u_Offset;
uniform vec2 u_TexCoord;

out vec2 v_TexCoord;

void main()
{
	float ratio = 9.0f / 16.0f;
	vec4 pos = gl_in[0].gl_Position;
	
	gl_Position = pos;
	v_TexCoord = u_TexCoord + vec2(0, u_Dimensions.y);
	EmitVertex();
	gl_Position = pos + 0.2f * vec4(0, u_Dimensions.y, 0, 0);
	v_TexCoord = u_TexCoord;
	EmitVertex();
	gl_Position = pos + 0.2f * ratio * vec4(u_Dimensions.x, 0, 0, 0);
	v_TexCoord = u_TexCoord + u_Dimensions;
	EmitVertex();
	gl_Position = pos + 0.2f * vec4(u_Dimensions.x * ratio, u_Dimensions.y, 0, 0);
	v_TexCoord = u_TexCoord + vec2(u_Dimensions.x, 0);
	EmitVertex();
	EndPrimitive();
}