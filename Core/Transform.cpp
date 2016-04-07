#include "Transform.hpp"

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4
Transform::getAsMat4()
{
  glm::mat4 translate = glm::translate(m_position);
  glm::mat4 rotate    = glm::rotate(m_orientation[0],
                                    glm::vec3(m_orientation[1]
                                             ,m_orientation[2]
                                             ,m_orientation[3])
                                    );
  glm::mat4 scale     = glm::scale(m_scale);
 
  return translate * rotate * scale;
}