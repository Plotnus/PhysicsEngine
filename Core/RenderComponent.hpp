/**
 * Thanks to articles and texts that informed this design.
 * in particular: "Game Engines 101: The Entity/Component Model" - Megan Fox
 */
#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include "BaseComponent.hpp"


class RenderComponent: public BaseComponent
{
public:
  RenderComponent(){}
  ~RenderComponent(){}

  /**
   * Registers the renderable mesh with the rendering system
   */
  virtual void
  Startup();
  /**
   * Removes the renderable mesh from the rendering system
   */
  virtual void
  Shutdown();
};

#endif
