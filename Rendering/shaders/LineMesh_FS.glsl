#version 330 core

// uniform variables, don't vary throughtout the mesh
uniform  vec3 u_Color;
out      vec3 o_fColor;

void
main()
{
  o_fColor = u_Color;
}