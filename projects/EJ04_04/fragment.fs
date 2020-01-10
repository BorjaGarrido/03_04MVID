#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main() {
    //Vertical flip activado con la negación de UV
     FragColor = texture2D(tex_1, UV);
 }