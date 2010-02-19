#version 150
precision highp float;
in vec3 DiffuseColor;
in float logFrag;
out vec4 gl_FragColor;
out float gl_FragDepth;

uniform sampler2D Diffuse;

void main(void) {
   gl_FragColor = vec4(DiffuseColor, 1.0);
    //gl_FragColor = vec4(1.0,1.0,1.0, 1.0);
 	const float C = 1.0;
	const float far = 1000000000.0;
	const float offset = 1.0;
    gl_FragDepth = (log(C * logFrag + offset) / log(C * far + offset));
}
