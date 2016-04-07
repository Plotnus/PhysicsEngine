#version 330 core

in vec3 color;

out vec3 fragment_color;

void
main()
{
  fragment_color = color;
}