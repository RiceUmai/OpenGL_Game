#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float Time;

void main()
{
    vec2 mosaic = TexCoords;
    mosaic = floor(mosaic * 50) / 50;
    vec3 col = texture(screenTexture, mosaic).rgb;

    FragColor = vec4(col, 1.0f);
}