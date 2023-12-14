attribute vec3 gpu_Vertex;
attribute vec2 gpu_TexCoord;
attribute vec4 gpu_Color;
uniform mat4 gpu_ModelViewProjectionMatrix;

uniform float Time;
uniform vec2 Resolution;

varying vec4 color;
varying vec2 texCoord;

void main(void)
{
	color = gl_Color;
	texCoord = vec2(gpu_TexCoord);
	//float depth = cos(Time) * .5;
	//vec3 offset = vec3(sin(Time) * Resolution.x * .5, cos(Time) * Resolution.y * .1, 1. - depth * 2.);
	//vec2 center = Resolution.xy * .5;
	//vec3 localPos = gpu_Vertex;
	//float angle = sin(Time * 3.) * .1;
	//mat2 rotMat = mat2(cos(angle), -sin(angle), sin(angle) * (1. + cos(Time * 4.2) * 0.25), cos(angle) * (1. + cos(Time * 4.2) * 0.25));
	//localPos.xy = rotMat * (localPos.xy - center) + center; // Rotation
	//localPos += offset; // Location
	//localPos.xy = (localPos.xy - center) / (1. + localPos.z) + center; // Perspective
	vec3 localPos = gpu_Vertex;
	gl_Position = gpu_ModelViewProjectionMatrix * vec4(localPos, 1.);
}