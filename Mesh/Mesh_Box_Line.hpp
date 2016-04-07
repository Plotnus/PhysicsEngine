#ifndef MESH_BOX_LINE_HPP
#define MESH_BOX_LINE_HPP

#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

#include "Mesh.hpp"


// Note that this is the base mesh that all boxes will translate into their representations
class Mesh_Box_Line : public Mesh
{
public:
  Mesh_Box_Line(){};
  ~Mesh_Box_Line(){};
  
  virtual void
  init(const char* texturePath) override;
  
  virtual void
  render(const glm::mat4 & mvp) const override;
  
  virtual void
  cleanup() override;
  
  
private:
  
  // static data for out base mesh
  static const GLfloat g_position_buffer_data[];
  static const GLfloat g_color_buffer_data[];
  
  // static data for base mesh again
  // Globals for our buffer and shader ID
  GLuint PositionBufferID;  // gl generated vert buffer id
  GLuint ColorBufferID;      // gl generated UV texture coord id
  GLuint ProgramID;       // gl generated shader program id
  GLuint mvpID;           // uniform mvp
};

#else

#endif
