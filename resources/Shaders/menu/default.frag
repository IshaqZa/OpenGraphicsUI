#version 330 core
out vec4 FragColor;

in vec4 color;

uniform sampler2D tex;


void main()
{
    FragColor = color;
}