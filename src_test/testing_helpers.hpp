#pragma once
#include "entity.hpp" 
#include "entity_changes_listener.hpp"
#include <unordered_map>

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

  
