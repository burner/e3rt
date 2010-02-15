#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Nor;
in vec2 in_Tex;

// mvpmatrix is the result of multiplying the model, view, and projection matrices */
uniform mat4 mvpmatrix;

out vec3 ex_Color;
out vec2 ex_Tex;
out float logFrag;

void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
	vec4 tmp = mvpmatrix * vec4(in_Position, 1.0);
    gl_Position = tmp;
    logFrag = tmp.z;
    ex_Color = vec3(in_Tex, 0.5);
	ex_Tex = in_Tex;	
}
