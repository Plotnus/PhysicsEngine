#version 330 core


layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
/*
//layout(location = 0) in vec3 vertexPositionBuffer_modelSpace;
layout(location = 1) in vec3 vertexNormalBuffer_modelSpace;

layout(location = 2) uniform vec3 lightPositionBuffer_worldSpace;
layout(location = 3) uniform vec3 lightIrradiance;

uniform mat4 transform_MVP;
uniform mat4 transform_modelToWorld;

uniform vec3 materialAmbientColor;
uniform vec3 materialDiffuseColor;
uniform vec3 materialSpecularColor;
*/

uniform mat4 MVP;
uniform mat4 M;

out vec3 fColor_in;
out vec3 fNormal_in;

void
main()
{
  gl_Position = MVP * vec4(vPosition, 1);
  fNormal_in =  (M * vec4(vNormal, 0)).xyz;
  //gl_Position = mvp * vec4(positionBuffer_modelSpace, 1);
  //normal      = vertexvertexNormalBuffer_modelSpace;
  //fNormal_in = vNormal;
  fColor_in = vColor;
}