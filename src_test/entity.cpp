#include "entity.hpp"
#include "gmock/gmock.h"
#include "testing_helpers.hpp"
#include <memory>

using namespace testing;

class EmptyEntity : public Test {
 public:
  Entity entity;
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

TEST_F(EmptyEntity, haveNoComponents) {
  ASSERT_FALSE(entity.hasComponent<TestComponent1>());
}

TEST_F(EmptyEntity, whenComponentAdded_haveThatComponent) {
  TestComponent1 *component1 = new TestComponent1();
  entity.addComponent(std::unique_ptr<TestComponent1>(component1));
  ASSERT_TRUE(entity.hasComponent<TestComponent1>());
}

TEST_F(EmptyEntity, whenSeveralComponentsAdded_haveAllOfThatComponents) {
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

TEST_F(EntityWith2Components, returnsProperComponentByClass) {
  ASSERT_THAT(&entity.getComponent<TestComponent1>(), Eq(c1));
  ASSERT_THAT(&entity.getComponent<TestComponent2>(), Eq(c2));
}

