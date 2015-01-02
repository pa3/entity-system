#pragma once

class Engine;

class System {
 public:
  virtual void update( double deltaTime ) = 0;
  void setEngine( Engine * e ) {
    engine = e;
  }
 protected:
  Engine * engine;
};
