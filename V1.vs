uniform float Scale;

void main(void)
{
vec4 a = gl_Vertex;
gl_Position = gl_ModelViewProjectionMatrix * a; // same as 
}


