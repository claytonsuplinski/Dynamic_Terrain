/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

in vec3 Position;
in vec3 Normal;
in vec3 vertPos;

const vec4 LightPosition = vec4(0.0, 0.0, 10.0, 0.0);
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Kd = vec3(0.6, 0.6, 0.6); // Diffuse reflectivity
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
const vec3 Ks = vec3(0.75, 0.75, 0.75); // Specular reflectivity
const float Shininess = 6.f; // Specular shininess factor
layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform ivec2 size;
uniform float time;

float vertOffset = tc.y + mod(time, 500)/500 + (tc.y + mod(time, 500)/500 > 1 ? -1 : 0);
//if(vertOffset > 1){vertOffset = vertOffset - 1;}
vec2 tc2 = vec2(tc.x, vertOffset);
//float textureOffset = mod(time, 1000)/1000;
//tc2.x = tc2.x + 0.5;
//if(tc2.x > 1){tc2.x = tc2.x - 1;}


vec4 color = texture(picture, tc2);

vec3 ads()
{
vec3 n = normalize( Normal );
vec3 s = normalize( vec3(LightPosition) - Position );
vec3 v = normalize(vec3(-Position));
vec3 r = reflect( -s, n );

return LightIntensity *
( Ka * vec3(color) +
Kd * vec3(color) * max( dot(s, n), 0.0 ));
}

void main()
{
	vec3 finalColor = vec3(color);

	float dist1 = abs( Position.z );
	float fogFactor = (5000.0f - dist1) /
	(5000.0f - 0.5f);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );

	vec3 fogColor = vec3(0.1f, 0.1f, 0.1f);
	if(size.y == 1){
		fogColor = vec3(0.1f, 0.1f, 0.1f);
	}
	else if(size.y == 2){
		fogColor = vec3(0.0f, 0.05f, 0.0f);
	}
	else if(size.y == 3){
		fogColor = vec3(0.3f, 0.3f, 0.1f);
	}
	else if(size.y == 4){
		fogColor = vec3(0.2f, 0.0f, 0.0f);
	}
	else if(size.y == 5){
		fogColor = vec3(0.0f, 0.0f, 0.05f);
	}

	//fogColor = vec3(0.23f, 0.38f, 0.545f);
	fogColor = vec3(0.486f, 0.596f, 0.737f);
	finalColor = vec3(mix( fogColor, finalColor, fogFactor ));

	finalColor = finalColor + vec3(0.045*sin(vertPos.z/100 - 3*time), 0.045*sin(vertPos.z/100 - 3*time), 0.045*sin(vertPos.z/100 - 3*time) + 0.05);

	//if(fract(sin(dot(Position.xy ,vec2(12.9898,78.233))) * 43758.5453) < 0.05){finalColor = finalColor + ((1000-abs(mod(vertPos.z, 2000)-1000))/500)*vec3(0.1, 0.1, 0.1);}

	fogColor = vec3(0.298f, 0.38f, 0.494f);
	finalColor = vec3(mix( fogColor, finalColor, fogFactor ));

	FragColor = vec4(finalColor, color.a);
}

