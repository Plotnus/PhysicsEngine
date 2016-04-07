#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Core/Light.hpp"
#include "Core/Model.hpp"
#include "Core/GameObject.hpp"

class Scene
{
public:
  Scene(){}
  ~Scene(){}
  
  void
  addLight(const Light& light)
  {
    lights.push_back(light);
  }
  
  void
  addModel(const Model& model)
  {
    models.push_back(model);
  }
  
  void
  addGameObject(const GameObject& gameobject)
  {
    gameObjects.push_back(gameobject);
  }
  
  // todo add removal
  
private:
  vector<Light*>      lights;       // light manager holds these
  vector<Model*>      models;       // model manager holds these
  vector<GameObject*> gameObjects;  // GameObjectManager holds these
};

#endif