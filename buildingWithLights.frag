/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

in vec4 color2;
in vec3 Position;
in vec3 Normal;
const vec4 LightPosition = vec4(0.0, 0.0, 0.0, 0.0);
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Kd = vec3(0.6, 0.6, 0.6); // Diffuse reflectivity
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform ivec2 size;
uniform float time;

vec4 color = texture(picture, tc);

vec3 ads()
{
vec3 n = normalize( Normal );
vec3 s = normalize( vec3(LightPosition) - Position );


return LightIntensity *
( Ka * vec3(color) +
Kd * vec3(color) * max( dot(s, n), 0.0 ));
}

void main()
{
	float dist1 = abs( Position.z );
	float fogFactor = (200.0f - dist1) /
	(200.0f - 0.5f);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );

	float fogFactorLight = (400.0f - dist1)/(400.0f - 0.5f);
	fogFactorLight = clamp( fogFactorLight, 0.0, 1.0 );

	float factor = time - 10*int(time/10);
	vec3 finalColor = 1*ads()+0.25*color2.xyz;
	if(finalColor.x < 0.8 && finalColor.y < 0.8 && finalColor.z < 0.8){
		finalColor = vec3(mix( vec3(0.1f, 0.1f, 0.1f), finalColor, fogFactor ));
	}
	else{
		finalColor = vec3(mix( vec3(0.1f, 0.1f, 0.1f), finalColor,  fogFactorLight ));
	}
	
	FragColor = vec4(finalColor, color2.a);
}

