#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
    vec4 color = texture(u_Texture, v_TexCoord);
    if (color.a == 0)
    {
        discard;
    }
    fragColor = color;
}