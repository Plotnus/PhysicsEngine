/**
 * Special thanks to websites and articles that helped to inform this
 * design: "Game Engines 101: The Entity/Component Model" - Megan Fox
 */
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include "BaseComponent.hpp"
#include "Model.hpp"
#include "Transform.hpp"

class GameObject
{
public:
  GameObject(){}
  ~GameObject(){}
  
  Model*     m_pModel; // this is a pointer because it refers to a model instance
  Transform m_transform;
  
  
  /**
   *
   */
  //TODO: switch to component based system
  
  
  
  /**
   * Returns the component referenced by "id"
   */
  //Component*
  //GetComponent(/* id */);
  /**
   * Returns true if *this has the component referenced by id
   */
 // bool
  //HasComponent(/*id*/);
  /**
   * Attatches the given component to this game object
   * @retval true if component successfully attached
   */
  //bool
  //AttachComponent(/*ComponentType, argumentList, name*/);
  /**
   * Removes the given component from *this
   * @retval true if component successfully attached
   */
  bool
  DetatchComponent(/*name*/);

  void
  UpdateComponents();

  void
  HandleMessage(/*MessageType message*/);

private:
  std::vector<BaseComponent> base_component_list;

};

#endif
