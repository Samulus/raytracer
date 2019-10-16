R""(#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D image;
uniform vec2 iResolution;

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution;
    FragColor = texture(image, uv);
})""
