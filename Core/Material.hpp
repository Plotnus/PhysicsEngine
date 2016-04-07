#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// include glm
#include <string>
#include <glm/glm.hpp>

struct Material
{
public:
  Material()
  :vertexshader(std::string("Phong_VS.glsl"))
  ,fragmentshader(std::string("Phong_FS.glsl"))
  {}
  
  Material( glm::vec3 colorAmbient_in
           ,glm::vec3 colorDiffuse_in
           ,glm::vec3 colorSpecular_in
           ,std::string vertexShader_in
           ,std::string fragmentShader_in
           );
  ~Material(){}
  Material(const Material& mat_in){}

  // normal map (aka bump map)
  // texture
  // shader

  //for the simplicity of this program we will just have
  // a color and no texture
  glm::vec3 colorAmbient;
  glm::vec3 colorDiffuse;
  glm::vec3 colorSpecular;
  
  const std::string vertexshader;
  const std::string fragmentshader;
  
  Material& operator=(const Material rhs){
    colorDiffuse  = rhs.colorDiffuse;
    colorAmbient  = rhs.colorAmbient;
    colorSpecular = rhs.colorSpecular;
    
    return *this;
  }
  
  static const Material Phong_Monochrome;
  static const Material Phong_Texture;
  
};



#endif
