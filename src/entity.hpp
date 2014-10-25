#pragma once
#include "class_id.hpp"
#include <unordered_map>
#include <memory>

class Entity {
 public:

  template<class T>
  void addComponent(std::unique_ptr<T> component);

  template<class T> 
  bool hasComponent();

  template<class T>
  T& getComponent();
  
private:
  std::unordered_map<int, void *> components;
};

template<class T>
bool Entity::hasComponent() {
  int classId = ClassId::ofType<T>();
  return components.find(classId) != components.end();
}

template<class T>
void Entity::addComponent(std::unique_ptr<T> component) {
  int classId = ClassId::ofInstance(*component);
  components[classId] = component.release();
}

template<class T>
T& Entity::getComponent() {
  return *static_cast<T*>(components[ClassId::ofType<T>()]);
}
 
