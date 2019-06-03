#version 330 core

in vec4 v_color;
in vec2 v_texCoord;

out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
void main()
{
    vec4 fragcolor = (texture(u_Texture, v_texCoord));
    if (fragcolor.a == 0)
    {
        discard;
    }
	color = fragcolor + v_color + u_Color;
}