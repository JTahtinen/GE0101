#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float u_ScreenRatio;

in VS_OUT
{
	vec2 size;
	vec4 color;
} gs_in[];

out vec4 v_Color;

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	vec2 size = gs_in[0].size;
	vec4 outcolor = gs_in[0].color;

	gl_Position = pos;
	v_Color = outcolor;
	EmitVertex();
	
	gl_Position = pos + vec4(0, size.y * u_ScreenRatio, 0, 0);
	v_Color = outcolor;
	EmitVertex();
	
	gl_Position = pos + vec4(size.x, 0, 0, 0);
	v_Color = outcolor;
	EmitVertex();
	
	gl_Position = pos + vec4(size.x, size.y * u_ScreenRatio, 0, 0);
	v_Color = outcolor;
	EmitVertex();
	
	EndPrimitive();
}