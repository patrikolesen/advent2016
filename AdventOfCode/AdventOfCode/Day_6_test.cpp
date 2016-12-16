#include "gtest\gtest.h"

#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

TEST(AdventOfCode6, Quest1)
{
  std::ifstream file("C:\\programming\\adventofcode\\input\\input6_1.txt");
  std::string str;
  std::map<char, int> charCount[10];
  char passwd[9];
  memset(passwd, 0, sizeof(passwd));

  while (std::getline(file, str))
  {
    for (int i = 0; i < 8; i++)
    {
      charCount[i][str[i]]++;
    }
  }
  for (int i = 0; i < 8; i++)
  {
    int max = 0;
    for (auto it = charCount[i].begin(); it != charCount[i].end(); it++)
    {
      if (max < it->second)
      {
        passwd[i] = it->first;
        max = it->second;
      }
    }
  }
  std::cout << " result : [" << passwd << "]" << std::endl;
}

TEST(AdventOfCode6, Quest2)
{
  std::ifstream file("C:\\programming\\adventofcode\\input\\input6_1.txt");
  std::string str;
  std::map<char, int> charCount[10];
  char passwd[9];
  memset(passwd, 0, sizeof(passwd));

  while (std::getline(file, str))
  {
    for (int i = 0; i < 8; i++)
    {
      charCount[i][str[i]]++;
    }
  }
  for (int i = 0; i < 8; i++)
  {
    int min = 999999;
    for (auto it = charCount[i].begin(); it != charCount[i].end(); it++)
    {
      if (min > it->second)
      {
        passwd[i] = it->first;
        min = it->second;
      }
    }
  }
  std::cout << " result : [" << passwd << "]" << std::endl;
}