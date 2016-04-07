#version 330 core


// input variables
in vec2 UV;
// input variables that are not interpolated for the duration of the mesh
uniform sampler2D myTextureSampler;

// output variables
out vec4 color;

void
main()
{
  color = texture(myTextureSampler, UV);
}

