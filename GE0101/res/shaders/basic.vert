#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;
layout (location = 3) in vec3 offset;

out vec4 v_color;
out vec2 v_texCoord;
out float v_lightIntensity;

uniform vec3 u_Offset;
uniform float u_ScrRatio;
uniform float u_Scale;


void main()
{
	float zDiv = -offset.z;
	float distanceFromLight = distance(vec3(position.xy, 0.5), vec3(1.0, 1.0, 0));
	if (distanceFromLight == 0.0)
	{
		v_lightIntensity = 1000.0f;
	} else {
		v_lightIntensity = 1.0 / distanceFromLight;
	}
	gl_Position = 
	vec4(position.x / zDiv, position.y * u_ScrRatio / zDiv, 0, 1) +
	vec4(offset.x / zDiv, offset.y * u_ScrRatio / zDiv, 0, 0);
	v_color = color;
	v_texCoord = texCoord;
}