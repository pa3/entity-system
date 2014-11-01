#pragma once
#include "class_id.hpp"
#include "entity_changes_listener.hpp"
#include <unordered_map>
#include <unordered_set>
#include <memory>

class Entity {
 public:

  template<class T>
  void addComponent( std::unique_ptr<T> component );

  template<class T> 
  bool hasComponent();

  bool hasComponent( int componentId );

  template<class T>
  T& getComponent();

  template<class T>
  void removeComponent();

  void addChangesListener( EntityChangesListener * listener );

private:
  void notifyChangeListeners();
  
  std::unordered_map<int, void *> components;
  std::unordered_set<EntityChangesListener *> changeListeners;
};

template<class T>
bool Entity::hasComponent() {
  return hasComponent(ClassId::ofType<T>());
}

template<class T>
void Entity::addComponent(std::unique_ptr<T> component) {
  int classId = ClassId::ofInstance(*component);
  components[classId] = component.release();
  notifyChangeListeners();
}

template<class T>
T& Entity::getComponent() {
  return *static_cast<T*>(components[ClassId::ofType<T>()]);
}

template<class T>
void Entity::removeComponent() {
  int classId = ClassId::ofType<T>();
  components.erase(classId);
  notifyChangeListeners();
}
 
