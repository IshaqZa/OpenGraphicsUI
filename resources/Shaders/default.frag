#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCo;
uniform sampler2D tex;
uniform int isTex;

void main()
{
    if(isTex == 1){
        FragColor = texture(tex, texCo);
    }else{
        FragColor = color;
    }
}