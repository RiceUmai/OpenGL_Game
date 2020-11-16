#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    float Alpha = texture(text, TexCoords).r;
    vec4 sampled = vec4(1.0, 1.0, 1.0, Alpha) ;
    // vec4 test = sampled * vec4(textColor, 1.0f);
    // if(Alpha == 0)
    // {
    //     test = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // }
    FragColor = sampled * vec4(textColor, 1.0f);
    //FragColor = test;
}

