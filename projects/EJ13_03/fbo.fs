#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

mat3 sx = mat3( 
    1.0, 2.0, 1.0, 
    0.0, 0.0, 0.0, 
   -1.0, -2.0, -1.0 );
mat3 sy = mat3( 
    1.0, 0.0, -1.0, 
    2.0, 0.0, -2.0, 
    1.0, 0.0, -1.0 );

uniform float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
uniform float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);
 
void main(void) {
    FragColor = texture(screenTexture, vec2(gl_FragCoord) / 1024.0) * weight[0];
    for (int i=1; i<3; i++) {
        FragColor +=texture(screenTexture, (vec2(gl_FragCoord) + vec2(0.0, offset[i])) / 1024.0)* weight[i];
        FragColor += texture(screenTexture, (vec2(gl_FragCoord) - vec2(0.0, offset[i])) / 1024.0)* weight[i];
    }
}

