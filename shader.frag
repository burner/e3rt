#version 150
precision highp float;
in vec3 ex_Color;
in vec2 ex_Tex;
in float logFrag;
out vec4 gl_FragColor;
out float gl_FragDepth;

uniform sampler2D Diffuse;

void main(void) {
    //gl_FragColor = vec4(ex_Color,1.0);
	gl_FragColor = texture2D(Diffuse, ex_Tex);
	const float C = 1.0;
	const float far = 1000000000.0;
	const float offset = 1.0;
    gl_FragDepth = (log(C * logFrag + offset) / log(C * far + offset));
}
