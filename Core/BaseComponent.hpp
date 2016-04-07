#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP

class BaseComponent
{
public:
  BaseComponent(){}
  ~BaseComponent(){}

  virtual void
  Startup();

  virtual void
  Update();

  virtual void
  Shutdown();

  virtual void
  HandleMessage(/*MessageType message*/);

};

#endif
