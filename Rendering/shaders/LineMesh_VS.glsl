#version 330 core


layout(location = 0) in vec3 vPosition;

uniform mat4 u_MVP;

void
main()
{
  gl_Position = u_MVP * vec4(vPosition, 1);
}