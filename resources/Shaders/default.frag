#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCo;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, texCo) * color;
}