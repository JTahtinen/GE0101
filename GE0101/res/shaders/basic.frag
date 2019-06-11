#version 330 core

in vec4 v_color;
in vec2 v_texCoord;
in float v_lightIntensity;

out vec4 color;


uniform sampler2D u_Texture;
uniform vec4 u_Color;
void main()
{
	//temp code
    vec4 fragcolor = (texture(u_Texture, v_texCoord));
    if (fragcolor.a == 0)
    {
        discard;
    }

	color = vec4(fragcolor.rgb * v_lightIntensity, fragcolor.a) + v_color + u_Color;
}