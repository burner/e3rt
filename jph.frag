#version 150
precision highp float;

in float logFrag;
in vec3 normal, eyeVec, lightDir, DiffuseColor, pos;
in vec2 ex_Tex;
out vec4 gl_FragColor;
out float gl_FragDepth;

const vec3 SkyColor = vec3(0.6,0.6,0.1);
const vec3 GroundColor = vec3(0.0,0.05,0.3);

uniform sampler2D Diffuse;
//uniform vec3 lightsource;

void main (void)
{
	
	
	//vec3 final_color= vec3(0.1, 0.1, 0.1);
	//vec3 final_color= noise3(pos.z);
	vec3 final_color = texture2D(Diffuse, ex_Tex).xyz * vec3(0.3, 0.3, 0.4);
	final_color *= texture2D(Diffuse, ex_Tex+vec2(0.03,0.03)).xyz * vec3(0.4, 0.3, 0.3)+ vec3(0.1,0.1,0.1);
	final_color+= (pos.y)*SkyColor*0.05;
	final_color+= (1.5-pos.y)*GroundColor*0.05;
	
	final_color+=DiffuseColor;//spherical harmonics from vs
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);

	float lambertTerm = dot(N,L);
				
	if(lambertTerm > 0.0)
	{
		final_color += vec3(0.5, 0.5, 0.25) * lambertTerm;	
		
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 180.0);
		final_color += vec3(specular);	
	}

	gl_FragColor = vec4(final_color,1.0);
	const float C = 1.0;
	const float far = 1000000000.0;
	const float offset = 1.0;
    gl_FragDepth = (log(C * logFrag + offset) / log(C * far + offset));

}
