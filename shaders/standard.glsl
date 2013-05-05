#define VERTEX_PROGRAM
#version 130

#ifdef VERTEX_PROGRAM

uniform mat4 matproj;
uniform mat4 matview;

in vec4 in_vertex;
in vec2 in_texture;
in vec4 in_color;

out vec2 texCoord;
out vec4 fcolor;

void main(void)
{
	gl_Position = matproj * matview * gl_Vertex; //in_vertex;
	
	texCoord = gl_MultiTexCoord0.xy; //in_texture;
	fcolor = gl_Color; //in_color;
	
}

#else
//#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D texture;

in vec2 texCoord;
in vec4 fcolor;

const vec3 degamma = vec3(1.0 / 2.2);
const vec3 gamma = vec3(2.2);

void main(void)
{
	vec4 color = texture2D(texture, texCoord);
	
	if (color.a < 0.25) discard;
	
	color.rgb = pow(color.rgb, degamma);
	
	color.rgb = mix(color.rgb, fcolor.rgb, fcolor.a);
	
	color.rgb = pow(color.rgb, gamma);
	
	/* luminance: 0.3 R + 0.59 G + 0.11 B
	gl_FragColor = vec4(vec3(color.r * 0.3 + color.g * 0.59 + color.b * 0.11), color.a);
	*/
	gl_FragColor = color;
}

#endif
