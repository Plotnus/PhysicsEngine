#ifndef LIGHT_HPP
#define LIGHT_HPP

//include glm

enum class LightType
{
  Point = 0,
  Directional,
  Spotlight
};

// Note to keep this project simple we will only be using
// one type of light
// this will either be directional or a point light.
class Light
{
public:
  Light(){}
  ~Light(){}

// the idea is that there are certain lights. Think of it
// like how lights are manufactured. Manufactured lights
// are all the same so we may just have several instances
// of a light. For this reason, we have a base light, and
// a light instance. Note that light instances are a Light,
// and a transform. Also note the analogue for Mesh and 
// MeshInstances.

private:
  glm::vec3 m_iradiance; // the energy of emmitance for each color
  LightType m_lightType;

};

#endif
