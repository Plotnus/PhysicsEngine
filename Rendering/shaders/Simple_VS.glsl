#version 330 core

// AttribArray inputs
layout(location = 0) in vec3 positionBuffer_modelSpace;
layout(location = 1) in vec3 colorBuffer;

//Uniform inputs
uniform mat4 mvp;

//output
out vec3 color;

void
main()
{
  gl_Position = mvp * vec4(positionBuffer_modelSpace, 1);
  
  color = colorBuffer;
}
