#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    //FragColor = vec4(1,1,1,1);
    FragColor = texture(texture1, TexCoords);
}