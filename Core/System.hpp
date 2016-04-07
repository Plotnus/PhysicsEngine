class System
{
public:
  virtual
  ~System() {}

  virtual void
  Update() = 0;

  virtual void
  Init() = 0;

  virtual void
  SendMessage(/*Message* msg*/) = 0;

};

