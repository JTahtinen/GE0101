#version 330 core

in vec4 v_color;
in vec2 v_texCoord;

out vec4 color;

uniform sampler2D u_Texture;

void main()
{
	color = (texture(u_Texture, v_texCoord)) + v_color;
}