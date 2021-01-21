#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float Time;

void main()
{
    vec3 col = texture(screenTexture, TexCoords + sin(Time)).rgb;

    FragColor = vec4(col, 1.0f);
}