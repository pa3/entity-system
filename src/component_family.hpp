#pragma once
#include "entity.hpp"
#include <unordered_set>
#include <vector>

using namespace std;

class ComponentFamily {
 public:
  ComponentFamily( vector<int> componentIds );
  
  void addIfFits( Entity * e );
  void removeIfDoesNotFit( Entity * e );
  void removeEntity( Entity * e );
  const unordered_set<Entity*>& getEntities();
 private:
  bool fits( Entity * e );
  unordered_set<Entity*> entities;
  vector<int> componentIds;
};
