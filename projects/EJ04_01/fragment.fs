#version 330 core

in vec2 UV;
in vec3 posColor;
out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main() {
    //FragColor = mix(texture(tex_1, UV), texture(tex_2, UV), 0.7);

    vec4 tex = texture2D(tex_1, UV);

    FragColor = tex + vec4(posColor , 1.0);
}
