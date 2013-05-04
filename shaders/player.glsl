#define VERTEX_PROGRAM
#version 130
precision mediump float;

#ifdef VERTEX_PROGRAM

uniform mat4 matproj;
uniform mat4 matview;
uniform float frame;

in vec3 in_vertex;
in vec3 in_texture;
in vec4 in_color;

out vec3 texCoord;
out vec4 fcolor;

void main(void)
{
	gl_Position = matproj * matview * vec4(in_vertex, 1.0);
	texCoord = in_texture;
	fcolor = in_color;
}

#else
#extension GL_EXT_gpu_shader4 : enable
uniform sampler2DArray texture;

in vec3 texCoord;
in vec4 fcolor;

const vec3 degamma = vec3(1.0 / 2.2);
const vec3 gamma = vec3(2.2);

void main(void)
{
	vec4 color = texture2DArray(texture, texCoord);
	
	/*
	if (color.a < 0.25) discard;
	
	color.rgb = pow(color.rgb, degamma);
	
	color.rgb = mix(color.rgb, fcolor.rgb, fcolor.a);
	
	color.rgb = pow(color.rgb, gamma);
	*/
	
	gl_FragColor = color;
}

#endif
