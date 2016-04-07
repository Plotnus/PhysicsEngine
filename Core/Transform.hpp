#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Component.hpp"

#include <glm/glm.hpp>

struct Transform : public Component
{
  glm::vec3 m_position;
  glm::vec3 m_scale;
  glm::vec4 m_orientation; // maybe make quaternion, depends on interfaces
  
  glm::mat4 getAsMat4();
};

#endif