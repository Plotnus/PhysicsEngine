#include "Material.hpp"


////////////////////////////////////////////////
// Static Const Definitions: for Material.hpp //
////////////////////////////////////////////////
const Material Material::Phong_Monochrome = Material(
                                             glm::vec3(0.2f,0.2f,0.2f)
                                            ,glm::vec3(0.4f,0.8f,0.3f)
                                            ,glm::vec3(0.3f,0.3f,0.3f)
                                            ,"Rendering/shaders/Phong_VS.glsl"
                                            ,"Rendering/shaders/Phong_FS.glsl"
                                            );






////////////////////////////////////////////////
// Constructor Definitions: for Material.hpp //
///////////////////////////////////////////////
Material::Material( glm::vec3 colorAmbient_in
                   ,glm::vec3 colorDiffuse_in
                   ,glm::vec3 colorSpecular_in
                   ,std::string vertexshader_in
                   ,std::string fragmentshader_in
                   )
:colorAmbient(colorAmbient_in)
,colorDiffuse(colorDiffuse_in)
,colorSpecular(colorSpecular_in)
,vertexshader(vertexshader_in)
,fragmentshader(fragmentshader_in)
{
  
}