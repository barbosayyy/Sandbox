#version 330 core
out vec4 fragColor;
  
struct Material{
    vec4 col;
};

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
uniform Material material;

void main()
{
    vec4 tex1 = texture(texture1, TexCoord);
    vec4 tex2 = texture(texture2, TexCoord);
    fragColor = mix(vec4(tex1.rgb, 1.0), vec4(tex2.rgb, tex2.a), mixValue) + material.col;
}