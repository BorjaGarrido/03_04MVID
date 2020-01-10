#version 330 core

in vec3 myColor;
out vec4 FragColor;

uniform vec3 addColor;

void main() {
    FragColor = vec4(myPos, 1.0);
}


//El resultado final es un triángulo totalmente negro. En ejercicios anterios el fragment recibía un valor por cada uno de los vértices que conformaban el triángulo. 
//El propio fragment se encargaba de interpolarlos, dando lugar a esos cambios de colores.
//En este caso, cada pixel dibujado por el fragment corresponde a un valor único, correspondiente a su vez al mismo punto de coordenadas del propio pixel.
//El fragment no es capaz de interporlar colores entre píxeles dando lugar al color negro.