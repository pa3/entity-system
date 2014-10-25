#pragma once
#include "entity.hpp"
#include <unordered_set>
#include <memory>

class Engine {
 public:
  void addEntity(std::unique_ptr<Entity> e);

  void removeEntity(Entity* e);

  template <class ... T>
  std::unordered_set<Entity *> filterEntities();

  std::unordered_set<Entity *> getEntities();
  
 private:
  std::unordered_set<std::unique_ptr<Entity>> entities;
};

template <class ... T>
std::unordered_set<Entity *> Engine::filterEntities() {
  std::unordered_set<Entity *> result;
  for ( auto& e : entities) {
    std::unordered_set<bool> componentsMap = {e->hasComponent<T>()...};
    if (componentsMap.find(false) == componentsMap.end()){
      result.insert(e.get());
    }
  }
  return result;
};

#include "engine.tpp"
