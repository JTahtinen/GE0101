#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float u_ScreenRatio;
//uniform float u_Scale;

in VS_OUT
{
	vec2 dimensions;
	vec2 texCoord;
	float scale;
} gs_in[];

out vec2 v_TexCoord;


void main()
{	
	vec2 dimensions = gs_in[0].dimensions;
	vec2 texCoord = gs_in[0].texCoord;
	float scale = gs_in[0].scale;
	vec2 finalDimensions = vec2(dimensions.x * scale, dimensions.y * scale * u_ScreenRatio);
	vec4 pos = gl_in[0].gl_Position;
	
	gl_Position = pos;
	v_TexCoord = texCoord + vec2(0, dimensions.y);
	EmitVertex();
	
	gl_Position = pos + vec4(0, finalDimensions.y, 0, 0);
	//gl_Position = pos + vec4(0, dimensions.y, 0, 0);
	v_TexCoord = texCoord;
	EmitVertex();
	
	gl_Position = pos + vec4(finalDimensions.x, 0, 0, 0);
	//gl_Position = pos + vec4(dimensions.x, 0, 0, 0);
	v_TexCoord = texCoord + dimensions;
	EmitVertex();
	
	gl_Position = pos + vec4(finalDimensions.x, finalDimensions.y, 0, 0);
	//gl_Position = pos + vec4(dimensions.xy, 0, 0);
	v_TexCoord = texCoord + vec2(dimensions.x, 0);
	EmitVertex();
	
	EndPrimitive();
}