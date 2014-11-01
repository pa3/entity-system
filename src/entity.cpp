#include "entity.hpp"

bool Entity::hasComponent( int componentId ) {
  return components.find(componentId) != components.end();
}

void Entity::addChangesListener(EntityChangesListener *listener) {
  changeListeners.insert( listener );
}

void Entity::notifyChangeListeners() {
  for (auto *listener : changeListeners ) {
    listener->componentsChanged(this);
  }
}
