#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Nor;
in vec2 in_Tex;

uniform mat3 NormalMatrix;
uniform mat4 MVPMatrix;


const float ScaleFactor=0.5;

const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;

// Constants for Old Town Square lighting
const vec3 L00  = vec3( 0.871297,  0.875222,  0.864470);
const vec3 L1m1 = vec3( 0.175058,  0.245335,  0.312891);
const vec3 L10  = vec3( 0.034675,  0.036107,  0.037362);
const vec3 L11  = vec3(-0.004629, -0.029448, -0.048028);
const vec3 L2m2 = vec3(-0.120535, -0.121160, -0.117507);
const vec3 L2m1 = vec3( 0.003242,  0.003624,  0.007511);
const vec3 L20  = vec3(-0.028667, -0.024926, -0.020998);
const vec3 L21  = vec3(-0.077539, -0.086325, -0.091591);
const vec3 L22  = vec3(-0.161784, -0.191783, -0.219152);

out vec3 DiffuseColor;
out float logFrag;

void main()
{

	// Multiply the mvp matrix by the vertex to obtain our final vertex position
	vec4 tmp = MVPMatrix * vec4(in_Position, 1.0);
    gl_Position = tmp; 
    logFrag = tmp.z;
    vec3 tnorm    = normalize( NormalMatrix * in_Nor);
    DiffuseColor =  C1 * L22 * (tnorm.x * tnorm.x - tnorm.y * tnorm.y) +
                    C3 * L20 * tnorm.z * tnorm.z +
                    C4 * L00 -
                    C5 * L20 +
                    2.0 * C1 * L2m2 * tnorm.x * tnorm.y +
                    2.0 * C1 * L21  * tnorm.x * tnorm.z +
                    2.0 * C1 * L2m1 * tnorm.y * tnorm.z +
                    2.0 * C2 * L11  * tnorm.x +
                    2.0 * C2 * L1m1 * tnorm.y +   
                    2.0 * C2 * L10  * tnorm.z;
    
    DiffuseColor *= ScaleFactor;
    
}
