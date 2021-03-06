#include "gmock/gmock.h"
#include "testing_helpers.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include <vector>

using namespace testing;
using namespace std;

class EngineWithThreeEntities : public ::testing::Test {
 public:
  Engine engine;
  Entity *e1, *e2, *e3;
  TestComponent1 *c1_1, *c1_2, *c1_3;
  TestComponent2 *c2_1, *c2_2;
  TestComponent3 *c3_1;
  TestComponent4 *c4;

  virtual void SetUp() {
    e1 = new Entity();
    e2 = new Entity();
    e3 = new Entity();

    c1_1 = new TestComponent1();
    c1_2 = new TestComponent1();
    c1_3 = new TestComponent1();
    c2_1 = new TestComponent2();
    c2_2 = new TestComponent2();
    c3_1 = new TestComponent3();
    c4 = new TestComponent4();

    engine.addEntity(unique_ptr<Entity>(e1));
    engine.addEntity(unique_ptr<Entity>(e2));
    engine.addEntity(unique_ptr<Entity>(e3));

    e1->addComponent(unique_ptr<TestComponent1>(c1_1));
    e1->addComponent(unique_ptr<TestComponent2>(c2_1));
    e1->addComponent(unique_ptr<TestComponent3>(c3_1));

    e2->addComponent(unique_ptr<TestComponent1>(c1_2));
    e2->addComponent(unique_ptr<TestComponent2>(c2_2));

    e3->addComponent(unique_ptr<TestComponent1>(c1_3));
 }
};

class EngineWithNoEntities : public ::testing::Test {
 public:
  Engine engine;
};


class EngineWithThreeSystems : public ::testing::Test {
 public:
  Engine engine;
  SpySystem *system1, *system2, *system3;
  OrderSpy orderSpy;

  virtual void SetUp() {
    system1 = new SpySystem( orderSpy );
    system2 = new SpySystem( orderSpy );
    system3 = new SpySystem( orderSpy );
    
    engine.addSystem( unique_ptr<System>(system1) );
    engine.addSystem( unique_ptr<System>(system2) );
    engine.addSystem( unique_ptr<System>(system3) );
  }
};

TEST_F(EngineWithThreeEntities, whenRemovedAllEntities_engineHaveNoEntities) {
  engine.removeEntity(e1);
  engine.removeEntity(e2);
  engine.removeEntity(e3);
  ASSERT_THAT(engine.getEntities(), IsEmpty());
}

TEST_F(EngineWithThreeEntities, whenRemovedOneEntity_engineHaveOtherTwoEntities) {
  engine.removeEntity(e1);

  ASSERT_THAT(engine.getEntities(), UnorderedElementsAre(e2, e3));
}

TEST_F(EngineWithThreeEntities, nothingIsFiltered) {
  auto filteredEntities = engine.filterEntities<TestComponent4>();
  ASSERT_THAT(filteredEntities, IsEmpty());
}

TEST_F(EngineWithThreeEntities, filterAllEntities) {
  auto filteredEntities = engine.filterEntities<TestComponent1>();
  ASSERT_THAT(filteredEntities, UnorderedElementsAre(e1, e2, e3));
}

TEST_F(EngineWithThreeEntities, filterSingleMatchingEntity) {
  auto filteredEntities = engine.filterEntities<TestComponent3>();
  ASSERT_THAT(filteredEntities, ElementsAre(e1));
}

TEST_F(EngineWithNoEntities, filterOutEverything){
  auto filteredEntities = engine.filterEntities<TestComponent1, TestComponent2>();
  ASSERT_THAT(filteredEntities, IsEmpty());
}

TEST_F(EngineWithThreeEntities, whenComponentRemovedFromEntity_doNotFilterEntityWithThisComponent){
  engine.filterEntities<TestComponent1>();
  
  e1->removeComponent<TestComponent1>();
  auto filteredEntities = engine.filterEntities<TestComponent1>();
  ASSERT_THAT(filteredEntities, UnorderedElementsAre(e2, e3));
}

TEST_F(EngineWithThreeEntities, whenComponentAddedToEntity_filterEntityWithThisComponent){
  engine.filterEntities<TestComponent4>();
  
  e1->addComponent(std::unique_ptr<TestComponent4>(c4));
  auto filteredEntities = engine.filterEntities<TestComponent4>();
  ASSERT_THAT(filteredEntities, ElementsAre(e1));
}

TEST_F(EngineWithThreeEntities, whenEntityRemoved_doNotFilterThisEntity){
  engine.filterEntities<TestComponent1>();
  
  engine.removeEntity(e1);
  auto filteredEntities = engine.filterEntities<TestComponent1>();
  ASSERT_THAT(filteredEntities, UnorderedElementsAre(e2, e3));
}

TEST_F(EngineWithThreeEntities, whenEntityAdded_thisEntityPresentsInFilterResults)
{
  engine.filterEntities<TestComponent1>();
  
  Entity * addedEntity = new Entity();
  TestComponent1 * c = new TestComponent1();
  addedEntity->addComponent(unique_ptr<TestComponent1>(c));
  engine.addEntity(unique_ptr<Entity>(addedEntity));
  
  auto filteredEntities = engine.filterEntities<TestComponent1>();
  ASSERT_THAT(filteredEntities, UnorderedElementsAre(e1, e2, e3, addedEntity));
}

TEST_F(EngineWithThreeSystems, whenEngineUpdated_systemsUpdatedInTheOrderTheyWereRegistered)
{
  engine.update(1.0);

  ASSERT_THAT( orderSpy.getSystemsUpdateOrder(), ElementsAre( system1, system2, system3 ));
}

TEST_F(EngineWithThreeSystems, whenEngineUpdated_systemsRecieveCorrectDeltaTime) {
  engine.update(2.0);
  ASSERT_THAT( system1->lastDeltaTime, Eq(2.0));
  ASSERT_THAT( system2->lastDeltaTime, Eq(2.0));
  ASSERT_THAT( system3->lastDeltaTime, Eq(2.0));
}

TEST_F(EngineWithThreeSystems, whenSystemIsAddedToEngine_engineInstanceProvidedToSystem) {
  ASSERT_THAT( system1->getEngine(), Eq( &engine ));
  ASSERT_THAT( system2->getEngine(), Eq( &engine ));
  ASSERT_THAT( system3->getEngine(), Eq( &engine ));
}

// TODO: should I introduce separate place for integrational tests
// like this one?
TEST_F(EngineWithThreeSystems, systemCanNicelyRemovesEntitiesDuringUpdate) {
  System * removingSystem = new EntitiesRemovingSystemFake();
  engine.addSystem(unique_ptr<System>(removingSystem));

  engine.update(1.0);
}
