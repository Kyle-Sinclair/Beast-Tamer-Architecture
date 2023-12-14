attribute vec3 gpu_Vertex;
uniform mat4 gpu_ModelViewProjectionMatrix;

void main(void)
{
	gl_Position = gpu_ModelViewProjectionMatrix * vec4(gpu_Vertex, 1.0);
}