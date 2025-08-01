#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    //FragColor = vec4(0.5f); // set all 4 vector values to 1.0
    FragColor = texture(texture_diffuse1, TexCoords);
}

