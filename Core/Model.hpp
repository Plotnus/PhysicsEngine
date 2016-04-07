#ifndef MODEL_HPP
#define MODEL_HPP

#include "Component.hpp"

#include "Material.hpp"
#include "Mesh.hpp"

// note we may render one model multiple times
// so, it is good if we just make on of each model
struct Model : public Component
{
  Model(){}
  ~Model(){}

  Material material;
  Mesh mesh;
};
#endif
