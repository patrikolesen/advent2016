#include "gtest\gtest.h"

#include <vector>
#include <algorithm>
#include <fstream>

class Triangle
{
public:
  Triangle() {}
  virtual ~Triangle() {}
  static bool validTriangle(std::vector<int> &sides)
  {
    std::sort(sides.begin(), sides.end());
    return ((sides[0] + sides[1]) > sides[2]);
  }
};

TEST(AdventOfCode3, OkTriangle)
{
  std::vector<int> sides = { 3, 4 ,5 };
  ASSERT_TRUE(Triangle::validTriangle(sides));
}

TEST(AdventOfCode3, OkTriangleSwapped)
{
  std::vector<int> sides = { 5, 4 ,3 };
  ASSERT_TRUE(Triangle::validTriangle(sides));
}

TEST(AdventOfCode3, InvalidTriangle)
{
  std::vector<int> sides = { 5, 10, 25 };
  ASSERT_FALSE(Triangle::validTriangle(sides));
}

TEST(AdventOfCode3, InvalidTriangleSwapped)
{
  std::vector<int> sides = { 25, 10, 5 };
  ASSERT_FALSE(Triangle::validTriangle(sides));
}

TEST(AdventOfCode3, Quest1)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input3_1.txt");
  std::string str;
  char *token = NULL;
  char *next_token = NULL;
  int count = 0;
  int total_count = 0;

  while (std::getline(file, str))
  {
    std::vector<int>sides;

    token = strtok_s((char*)str.c_str(), " ", &next_token);
    while (token)
    {
      sides.push_back(atoi(token));
      token = strtok_s(NULL, " ", &next_token);
    }
    total_count++;
    if (!Triangle::validTriangle(sides))
      count++;
  }
  std::cout << count << " of " << total_count << " is fake" << std::endl;
  std::cout << total_count-count << " of " << total_count << " is possible" << std::endl;
}

TEST(AdventOfCode3, Quest2)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input3_1.txt");
  std::string str;
  char *token = NULL;
  char *next_token = NULL;
  int count = 0;
  int total_count = 0;

  while (std::getline(file, str))
  {
    std::vector<int>sides[3];
    for (int row = 0; row < 3; row++) {
      int i = 0;
      token = strtok_s((char*)str.c_str(), " ", &next_token);
      while (token)
      {
        sides[i++].push_back(atoi(token));
        token = strtok_s(NULL, " ", &next_token);
      }
      total_count++;
      if (row < 2)
        std::getline(file, str);
    }
    for (int i = 0; i < 3; i ++)
      if (!Triangle::validTriangle(sides[i]))
        count++;
  }
  std::cout << count << " of " << total_count << " is fake" << std::endl;
  std::cout << total_count - count << " of " << total_count << " is possible" << std::endl;
}