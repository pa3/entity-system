#include "engine.hpp"
#include <algorithm>

void Engine::componentsChanged( Entity * e ) {
  for ( auto it = familyById.begin(); it != familyById.end(); it++ ) {
    it->second->addIfFits( e );
    it->second->removeIfDoesNotFit( e );
  }
}

void Engine::addEntity(std::unique_ptr<Entity> e) {
  auto entity = e.get();
  entity->addChangesListener(this);
  entities.insert(std::move(e));
  for ( auto it = familyById.begin(); it != familyById.end(); it++ ) {
    it->second->addIfFits( entity );
  }
}

void Engine::removeEntity(Entity *e) {
  auto iterator = find_if(entities.begin(), entities.end(), [e] (const std::unique_ptr<Entity>& p) { return p.get() == e; } );
  if ( iterator != entities.end() ) {
    entities.erase( iterator );
  }
  for ( auto it = familyById.begin(); it != familyById.end(); it++ ) {
    it->second->removeEntity(e);
  }
}

std::unordered_set<Entity *> Engine::getEntities() {
  std::unordered_set<Entity *> result;
  for ( auto& e : entities ) {
    result.insert( e.get() );
  }
  return result;
}
