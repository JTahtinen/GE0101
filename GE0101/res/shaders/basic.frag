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
	vec4 lightColor = vec4(1.0, 0.7, 0.7, 0) * v_lightIntensity;
    vec4 fragcolor = (texture(u_Texture, v_texCoord));
 	color = vec4(fragcolor.rgb * lightColor.rgb, fragcolor.a) + v_color + u_Color;
}