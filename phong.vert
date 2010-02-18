#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Nor;
in vec2 in_Tex;

// mvpmatrix is the result of multiplying the model, view, and projection matrices */
uniform mat4 mvpmatrix;
uniform mat4 pmatrix;
uniform vec3 lightsource;

out vec3 color;
out float logFrag;

//void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
//	vec4 tmp = mvpmatrix * vec4(in_Position, 1.0);
//	lightDir= (pmatrix * vec4(1.0,5.0,1.0,1.0)).xyz;
//	lightDir -= tmp.xyz;
//	normal=in_Nor;
    //eyeVec = -tmp.xyz;
    //gl_Position = tmp;
    //logFrag = tmp.z;
//}


	void main() {
	
		vec3 normal, lightDir;
		float NdotL;
		vec4 tmp = mvpmatrix * vec4(in_Position, 1.0);
		normal = normalize(in_Nor);
		
		lightDir = normalize(vec3(1.0, 4.0, -3.0));
		NdotL = max(dot(normal, lightDir), 0.0);
		
		color =  NdotL * vec3(0.5,0.6,0.5);
		//color=lightsource;
		
		gl_Position = tmp;
		logFrag = tmp.z;
	}
