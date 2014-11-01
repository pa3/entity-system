#pragma once

class Entity;
class EntityChangesListener {
 public:
  virtual void componentsChanged( Entity * e ) = 0;
};
