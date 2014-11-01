#pragma once
#include "entity.hpp"
#include "component_family_id.hpp"
#include <unordered_set>
#include <memory>
#include <vector>
#include "component_family.hpp"
#include "entity_changes_listener.hpp"

using namespace std;

class Engine : public EntityChangesListener {
 public:
  void addEntity(unique_ptr<Entity> e);

  void removeEntity(Entity* e);

  template <class ... T>
  unordered_set<Entity *> filterEntities();

  unordered_set<Entity *> getEntities();

  void componentsChanged( Entity * );
  
 private:
  unordered_map<int, unique_ptr<ComponentFamily>> familyById ; 
  unordered_set<unique_ptr<Entity>> entities;
};

template <class ... T>
unordered_set<Entity *> Engine::filterEntities() {
  static const auto familyId = ComponentFamilyId::ofTypes<T...>();
  if (familyById.find(familyId) == familyById.end()) {
    auto componentIds = {ClassId::ofType<T>()...};
    ComponentFamily * family = new ComponentFamily(componentIds);
    familyById[familyId] = unique_ptr<ComponentFamily>(family);
    for ( auto& e: entities )
      family->addIfFits( e.get() );
  }
  return familyById[familyId]->getEntities();
}

#include "engine.tpp"
