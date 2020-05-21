#vertex
#version 460

in vec3 l_position;

void main()
{
  gl_Position = vec4(l_position, 1.0);
}

#fragment
#version 460

out vec4 color;

void main()
{
  color = vec4(1.0, 1.0, 1.0, 1.0);
}