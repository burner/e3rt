#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Color;

// mvpmatrix is the result of multiplying the model, view, and projection matrices */
uniform mat4 mvpmatrix;

out vec3 ex_Color;
void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
    gl_Position = mvpmatrix * vec4(in_Position, 1.0);
    
    ex_Color = in_Color;
}
