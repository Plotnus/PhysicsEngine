#ifndef MESH_HPP
#define MESH_HPP

class Mesh
{
  
public:
  virtual ~Mesh(){}
  
  virtual void
  init(const char* texturePath) = 0;
  
  virtual void
  render(const glm::mat4 & mvp)const = 0;
  
  virtual void
  cleanup() = 0;
};


#endif