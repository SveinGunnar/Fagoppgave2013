#define VERTEX_PROGRAM
#version 130

#ifdef VERTEX_PROGRAM

out vec2 texCoord;

void main(void)
{
	gl_Position = vec4(gl_Vertex.xy * 2.0 - 1.0, 0.0, 1.0);
	texCoord = gl_Vertex.xy;
}

#else

uniform sampler2D texture;
uniform float frame;
uniform float mixlevel;
uniform float waves;

in vec2 texCoord;

const vec3 degamma = vec3(1.0 / 2.2);
const vec3 gamma = vec3(2.2);

void main(void)
{
	// wavy screen
	vec2 t = texCoord;
	t.x += sin(frame * 0.005 + t.y * 8.0) * 0.04 * waves;
	
	// using mipmap levels for blur
	vec4 color = texture2DLod(texture, t, mixlevel * 2.5);
	
	// luminance: 0.3 R + 0.59 G + 0.11 B
	vec4 luma = vec4(vec3(color.r * 0.3 + color.g * 0.59 + color.b * 0.11), color.a);
	
	// mix in grayscale based on mixlevel
	gl_FragColor = mix(color, luma, mixlevel);
}

#endif
