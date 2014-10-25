#include "class_id.hpp"
#include "gmock/gmock.h"
#include "testing_helpers.hpp"

using namespace testing;

TEST(ClassId, sameClassesHaveSameId) {
  ASSERT_THAT(ClassId::ofType<TestComponent1>(), Eq(ClassId::ofType<TestComponent1>()));
  ASSERT_THAT(ClassId::ofType<TestComponent2>(), Eq(ClassId::ofType<TestComponent2>()));
  ASSERT_THAT(ClassId::ofType<TestComponent3>(), Eq(ClassId::ofType<TestComponent3>()));
}

TEST(ClassId, differentClassesHaveDifferentIds) {
  ASSERT_THAT(ClassId::ofType<TestComponent1>(), Ne(ClassId::ofType<TestComponent2>()));
  ASSERT_THAT(ClassId::ofType<TestComponent2>(), Ne(ClassId::ofType<TestComponent3>()));
  ASSERT_THAT(ClassId::ofType<TestComponent3>(), Ne(ClassId::ofType<TestComponent4>()));
}

TEST(ClassId, instancesOfSameClassHaveSameId) {
  TestComponent1 c1_1, c1_2;
  TestComponent2 c2_1, c2_2;
  
  ASSERT_THAT(ClassId::ofInstance(c1_1), Eq(ClassId::ofInstance(c1_2)));
  ASSERT_THAT(ClassId::ofInstance(c2_1), Eq(ClassId::ofInstance(c2_2)));
}

TEST(ClassId, instancesOfDiffrerentClassesHaveDifferentIds) {
  TestComponent1 c1;
  TestComponent2 c2;
  
  ASSERT_THAT(ClassId::ofInstance(c1), Ne(ClassId::ofInstance(c2)));
}

TEST(ClassId, instanceAndClassOfThisInstanceHaveSameClassId) {
  TestComponent1 c1;
  TestComponent2 c2;
  
  ASSERT_THAT(ClassId::ofInstance(c1), Eq(ClassId::ofType<TestComponent1>()));
  ASSERT_THAT(ClassId::ofInstance(c2), Eq(ClassId::ofType<TestComponent2>()));
}

TEST(ClassId, instanceOfOneClassAndSomeOtherClassHaveDifferentClassIds) {
  TestComponent1 c1;
  TestComponent2 c2;
  
  ASSERT_THAT(ClassId::ofInstance(c1), Ne(ClassId::ofType<TestComponent2>()));
  ASSERT_THAT(ClassId::ofInstance(c2), Ne(ClassId::ofType<TestComponent1>()));
}
