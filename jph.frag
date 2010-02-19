#version 150
precision highp float;

in float logFrag;
in vec3 normal, eyeVec, lightDir, DiffuseColor;
out vec4 gl_FragColor;
out float gl_FragDepth;

uniform sampler2D Diffuse;
//uniform vec3 lightsource;

void main (void)
{
	
	vec3 final_color= vec3(0.1, 0.1, 0.15)+DiffuseColor;//ambient
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);

	float lambertTerm = dot(N,L);
				
	if(lambertTerm > 0.0)
	{
		final_color += vec3(0.2, 0.2, 0.4) * lambertTerm;	
		
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 100.0);
		final_color += vec3(specular);	
	}

	gl_FragColor = vec4(final_color,1.0);
	const float C = 1.0;
	const float far = 1000000000.0;
	const float offset = 1.0;
    gl_FragDepth = (log(C * logFrag + offset) / log(C * far + offset));

}
