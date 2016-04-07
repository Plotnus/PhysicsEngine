#version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 uv_coordinates;

out vec2 UV;

void
main()
{
  // Output position of the vertex, in clip space
  // map [0 .. 800][0 .. 600] to [-1 .. 1] [-1 .. 1]
  vec2 vertexPosition_homogenousspace = vertexPosition_screenspace - vec2(400, 300);
  vertexPosition_homogenousspace /= vec2(400, 300);
  gl_Position = vec4(vertexPosition_homogenousspace, 0, 1);
  
  // UV doesn't get transformed
  UV = uv_coordinates;
}