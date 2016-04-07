#version 330 core

// input variables, interpolate value
in      vec3 fColor_in;
in      vec3 fNormal_in;
// output variables
out     vec3  fColor;

void
main()
{
  // just a quick version for testing/ getting the pipeline going
  vec3  lightDirection = vec3(1,1,1);
  float lightPower = 100;
  
  
  // ambient contribution
  fColor  = fColor_in * 0.3;
  // diffuse contribution
  fColor += clamp(dot(fNormal_in, lightDirection), 0, 1)* fColor_in;
  
  
}