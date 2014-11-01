#include "component_family.hpp"

ComponentFamily::ComponentFamily(std::vector<int> componentIds) : componentIds(componentIds) {}

bool ComponentFamily::fits(Entity *e) {
  for (int id : componentIds)
    if (!e->hasComponent(id))
      return false;
  return true;
}

void ComponentFamily::addIfFits(Entity *e) {
  if (fits(e))
    entities.insert(e);
}

void ComponentFamily::removeIfDoesNotFit(Entity *e) {
  if (!fits(e))
    removeEntity(e);
}

void ComponentFamily::removeEntity(Entity *e) {
  entities.erase(e);
}

const std::unordered_set<Entity *>& ComponentFamily::getEntities() { return entities; }

