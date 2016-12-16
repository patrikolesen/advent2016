#include "Walker.h"
#include "gtest\gtest.h"

TEST(AdventOfCode1, InitialTest)
{
  Walker walker;
  const std::string input = "R2, L3";
  ASSERT_EQ(walker.walk((char*)input.c_str()), 5);
}

TEST(AdventOfCode1, TurnRight)
{
  Walker walker;
  const std::string input = "R2, R2, R2, R2, R2";
  ASSERT_EQ(walker.walk((char*)input.c_str()), 2);
}

TEST(AdventOfCode1, TurnLeft)
{
  Walker walker;
  const std::string input = "L2, L2, L2, L2, L2";
  ASSERT_EQ(walker.walk((char*)input.c_str()), 2);
}

TEST(AdventOfCode1, TestStep1)
{
  const std::string input = "R3, L2, L2, R4, L1, R2, R3, R4, L2, R4, L2, L5, L1, R5, R2, R2, L1, R4, R1, L5, L3, R4, R3, R1, L1, L5, L4, L2, R5, L3, L4, R3, R1, L3, R1, L3, R3, L4, R2, R5, L190, R2, L3, R47, R4, L3, R78, L1, R3, R190, R4, L3, R4, R2, R5, R3, R4, R3, L1, L4, R3, L4, R1, L4, L5, R3, L3, L4, R1, R2, L4, L3, R3, R3, L2, L5, R1, L4, L1, R5, L5, R1, R5, L4, R2, L2, R1, L5, L4, R4, R4, R3, R2, R3, L1, R4, R5, L2, L5, L4, L1, R4, L4, R4, L4, R1, R5, L1, R1, L5, R5, R1, R1, L3, L1, R4, L1, L4, L4, L3, R1, R4, R1, R1, R2, L5, L2, R4, L1, R3, L5, L2, R5, L4, R5, L5, R3, R4, L3, L3, L2, R2, L5, L5, R3, R4, R3, R4, R3, R1";
  Walker walker;
  ASSERT_EQ(walker.walk((char*)input.c_str()), 262);
//  app1((char*)input.c_str());
}
