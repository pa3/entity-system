#include "component_family.hpp"
#include "class_id.hpp"
#include "gmock/gmock.h"
#include "testing_helpers.hpp"

using namespace testing;


class ComponentFamilyWithOneComponent : public Test {
 public:
  ComponentFamily family;
  Entity * e1, * e2, * e3, * e4;
  TestComponent1 * c1_1, *c1_2, *c1_3;
  TestComponent2 * c2;
  TestComponent3 * c3;
  TestComponent4 * c4;

  ComponentFamilyWithOneComponent() : family({ClassId::ofType<TestComponent1>()}) {};

  virtual void SetUp() {
    e1 = new Entity();
    e2 = new Entity();
    e3 = new Entity();
    e4 = new Entity();
    c1_1 = new TestComponent1();
    c1_2 = new TestComponent1();
    c1_3 = new TestComponent1();
    c2 = new TestComponent2();
    c3 = new TestComponent3();
    c4 = new TestComponent4();
  
    e1->addComponent(std::unique_ptr<TestComponent1>(c1_1));
    e1->addComponent(std::unique_ptr<TestComponent2>(c2));
    e2->addComponent(std::unique_ptr<TestComponent1>(c1_2));
    e2->addComponent(std::unique_ptr<TestComponent3>(c3));
    e3->addComponent(std::unique_ptr<TestComponent1>(c1_3));
    e4->addComponent(std::unique_ptr<TestComponent4>(c4));
  }

};

TEST_F(ComponentFamilyWithOneComponent, addsEntities) {
  family.addIfFits(e1);
  family.addIfFits(e2);
  family.addIfFits(e3);

  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e1, e2, e3) );
}

TEST_F(ComponentFamilyWithOneComponent, doNoAddsEntityTwice) {
  family.addIfFits(e1);
  family.addIfFits(e1);

  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e1) );
}

TEST_F(ComponentFamilyWithOneComponent, doNotAddsEntityIfItNotMatch) {
  family.addIfFits(e4);
  ASSERT_THAT(family.getEntities(), IsEmpty());
}

TEST_F(ComponentFamilyWithOneComponent, removesEntity) {
  family.addIfFits(e1);
  family.addIfFits(e2);
  family.removeEntity(e1);

  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e2));
}

TEST_F(ComponentFamilyWithOneComponent, whenRequestedToRemoveMissingEntity_doNothing) {
  family.addIfFits(e1);
  family.removeEntity(e2);

  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e1));
}

TEST_F(ComponentFamilyWithOneComponent, whenRequestedToRemvoeUnfitEntity_removeIt) {
  family.addIfFits(e1);
  family.addIfFits(e2);
  e1->removeComponent<TestComponent1>();
  family.removeIfDoesNotFit(e1);
 
  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e2));
}

TEST_F(ComponentFamilyWithOneComponent, whenRequestedToRemoveUnfitEntityWhichActuallyFits_doNothing) {
  family.addIfFits(e1);
  family.addIfFits(e2);
  family.removeIfDoesNotFit(e1);
 
  ASSERT_THAT(family.getEntities(), UnorderedElementsAre(e1, e2));
}
