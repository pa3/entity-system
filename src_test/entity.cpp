#include "entity.hpp"
#include "gmock/gmock.h"
#include "testing_helpers.hpp"
#include <memory>

using namespace testing;


class EmptyEntity : public Test {
 public:
  Entity entity;
};

class TwoEmptyEntities : public Test {
 public:
  Entity e1;
  Entity e2;
};


class EntityWith2Components : public Test {
 public:
  Entity entity;
  TestComponent1 *c1;
  TestComponent2 *c2;
  
  virtual void SetUp() {
    c1 = new TestComponent1();
    c2 = new TestComponent2();
    
    entity.addComponent(std::unique_ptr<TestComponent1>(c1));
    entity.addComponent(std::unique_ptr<TestComponent2>(c2));
  }
};

TEST_F(EmptyEntity, hasNoComponents) {
  ASSERT_FALSE(entity.hasComponent<TestComponent1>());
}

TEST_F(EmptyEntity, whenComponentAdded_hasThatComponent) {
  TestComponent1 *component1 = new TestComponent1();
  entity.addComponent(std::unique_ptr<TestComponent1>(component1));
  ASSERT_TRUE(entity.hasComponent<TestComponent1>());
}

TEST_F(EmptyEntity, whenSeveralComponentsAdded_hasAllOfThatComponents) {
  TestComponent1 *component1 = new TestComponent1();
  TestComponent2 *component2 = new TestComponent2();
  TestComponent3 *component3 = new TestComponent3();
  
  entity.addComponent(std::unique_ptr<TestComponent1>(component1));
  entity.addComponent(std::unique_ptr<TestComponent2>(component2));
  entity.addComponent(std::unique_ptr<TestComponent3>(component3));

  ASSERT_TRUE(entity.hasComponent<TestComponent1>());
  ASSERT_TRUE(entity.hasComponent<TestComponent2>());
  ASSERT_TRUE(entity.hasComponent<TestComponent3>());
}

TEST_F(EntityWith2Components, hasBothComponents) {
  ASSERT_TRUE(entity.hasComponent<TestComponent1>());
  ASSERT_TRUE(entity.hasComponent<TestComponent2>());
}

TEST_F(EntityWith2Components, returnsProperComponentByClass) {
  ASSERT_THAT(&entity.getComponent<TestComponent1>(), Eq(c1));
  ASSERT_THAT(&entity.getComponent<TestComponent2>(), Eq(c2));
}

TEST_F(EntityWith2Components, removesComponent) {
  entity.removeComponent<TestComponent1>();
  ASSERT_FALSE(entity.hasComponent<TestComponent1>());
}

TEST_F(EntityWith2Components, checkIfHasComponentByComponentId) {
  ASSERT_TRUE(entity.hasComponent(ClassId::ofType<TestComponent1>()));
  ASSERT_TRUE(entity.hasComponent(ClassId::ofType<TestComponent2>()));
  ASSERT_FALSE(entity.hasComponent(ClassId::ofType<TestComponent3>()));
}

TEST_F(TwoEmptyEntities, whenEntityWasNotChanged_doNotNotifyEnitityChangedListeners) {
  TestEntityChangesListener listener;
  e1.addChangesListener(&listener);
  e2.addChangesListener(&listener);

  ASSERT_THAT(listener.amountOfNotificationsSentAbout(&e1), Eq(0));
  ASSERT_THAT(listener.amountOfNotificationsSentAbout(&e2), Eq(0));
}

TEST_F(TwoEmptyEntities, whenComponentAddedToEntity_notifyEnitityChangedListeners) {
  TestEntityChangesListener listener;
  e1.addChangesListener(&listener);
  e2.addChangesListener(&listener);

  e1.addComponent(std::unique_ptr<TestComponent1>(new TestComponent1()));
  e1.addComponent(std::unique_ptr<TestComponent2>(new TestComponent2()));
  
  e2.addComponent(std::unique_ptr<TestComponent3>(new TestComponent3()));

  ASSERT_THAT(listener.amountOfNotificationsSentAbout(&e1), Eq(2));
  ASSERT_THAT(listener.amountOfNotificationsSentAbout(&e2), Eq(1));
}

