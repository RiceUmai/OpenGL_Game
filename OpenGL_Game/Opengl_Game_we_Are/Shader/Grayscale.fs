#version 330 core
#define R_LUMINANCE 0.298912
#define G_LUMINANCE 0.586611
#define B_LUMINANCE 0.114478

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float Time;
const vec3 monochromeScale = vec3(R_LUMINANCE, G_LUMINANCE , B_LUMINANCE);

void main()
{
    vec4 col = texture(screenTexture, TexCoords);
    float grayColor = dot(col.rgb, monochromeScale);
    col = vec4(vec3(grayColor), 1.0);
    //float average = (0.2126 * col.r, + 0.7152 * col.g + 0.0722 * col.b) / 3.0;
    //FragColor = vec4(average, average, average, 1.0f);
    FragColor = col;
}