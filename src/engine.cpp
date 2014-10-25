#include "engine.hpp"
#include <algorithm>

void Engine::addEntity(std::unique_ptr<Entity> e) {
  entities.insert(std::move(e));
}

void Engine::removeEntity(Entity *e) {
  auto iterator = find_if(entities.begin(), entities.end(), [e] (const std::unique_ptr<Entity>& p) { return p.get() == e; } );
  if ( iterator != entities.end() ) {
    entities.erase( iterator );
  }
}

std::unordered_set<Entity *> Engine::getEntities() {
  std::unordered_set<Entity *> result;
  for ( auto& e : entities ) {
    result.insert( e.get() );
  }
  return result;
}
