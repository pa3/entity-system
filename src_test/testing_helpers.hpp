#pragma once
#include "entity.hpp" 
#include "entity_changes_listener.hpp"
#include "system.hpp"
#include <unordered_map>
#include "engine.hpp"

class TestComponent1 {};
class TestComponent2 {};
class TestComponent3 {};
class TestComponent4 {};

class TestEntityChangesListener : public EntityChangesListener {
 public:
  virtual void componentsChanged( Entity * e ) {
    if (!amountOfNotifications.count(e))
      amountOfNotifications[e] = 1;
    else 
      amountOfNotifications[e]++;
  }
  
  int amountOfNotificationsSentAbout( Entity * e ) {
    if (!amountOfNotifications.count(e))
      return 0;
    else 
      return amountOfNotifications[e];
  }
  
 private:
  std::unordered_map<Entity *, int> amountOfNotifications;
};

class OrderSpy {
 public:
  const std::vector<System*>& getSystemsUpdateOrder() { return updateInvokations; };
  void updated( System * s ) { updateInvokations.push_back( s ); };
 private:
  std::vector<System*> updateInvokations;
};

class SpySystem : public System {
 public:
  SpySystem( OrderSpy & spy) : orderSpy(spy) {};
  void update( double deltaTime ) {
    lastDeltaTime = deltaTime;
    orderSpy.updated(this);
  };

  Engine* getEngine() {
    return engine;
  }
  
  double lastDeltaTime;
 private:
  OrderSpy& orderSpy;
};

class EntitiesRemovingSystemFake : public System {
 public:
  void update (double deltaTime) {
    for ( auto* e :  engine->filterEntities<TestComponent1>() ) {
      engine->removeEntity(e);
    }
  }
};


