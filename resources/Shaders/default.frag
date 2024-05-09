#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCo;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform bool isTex;

void main()
{
    if(isTex){
        FragColor = texture(tex1, texCo);
    }else{
        FragColor = color;
    }
}