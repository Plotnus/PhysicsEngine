#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include <vector>
#include "../Core/GameObject.hpp"
#include "../Core/Light.hpp"

class RenderManager
{
public:
  RenderManager(){}
  
  void
  addRenderable(GameObject* gameObject);
  /**
   *
   */
  void
  init();
  /**
   * Registers a new base model to be rendered with this system
   * currently all models will have their own vao, this is only practical here
   * because of the small number of models
   */
  void
  registerModel(Model* pModel);
  /**
   * Renders all renderable objects
   */
  void
  render( const glm::mat4& view_transform
         ,const glm::mat4& projection_transform
         );
  
  
  std::vector<Transform*> boxTransforms; // for testing, REMOVE
private:
  std::vector<GameObject*> m_renderableObjects;
  std::vector<Light*>     lights;
  
  std::vector<Model*>     m_registeredModels;
  
  
};

#endif