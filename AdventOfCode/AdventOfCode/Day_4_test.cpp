#include "gtest\gtest.h"


#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <cstdlib>
#include <functional>



int getRoomNumber(const std::string& str)
{
  std::unordered_map<char, int> charCount;
  unsigned int pos = 0;
  int num = 0;

  /* Calculate chars */
  for (pos = 0; pos < str.length(); pos++)
  {
    if (str[pos] == '-')
      continue;
    if (str[pos] == '[')
      break;
    if (isdigit(str[pos])) {
      num = num * 10 + str[pos] - '0';
    }
    else {
      charCount[str[pos]] += 1;
    }
  }

  /* Sort */
  std::vector<std::pair<char, int>> sortedList;
  for (auto &character : charCount) {
    sortedList.push_back(character);
  }

  std::sort(sortedList.begin(), sortedList.end(), [=](std::pair<char, int>& a, std::pair<char, int>& b)
  {
    return a.second != b.second ? a.second > b.second : a.first < b.first;
  });
  pos++;

  bool checkSumOk = true;
  for (unsigned int j = 0; pos < str.length(); pos++, j++) {
    if (str[pos] == ']')
      break;

    if (str[pos] != sortedList[j].first) {
      checkSumOk = false;
      break;
    }
  }

  if (checkSumOk) {
    return num;
  }
  return 0;
}

std::string decryptRoom(const std::string & room) {
  std::string name;
  int number = getRoomNumber(room);
  if (number == 0)
    return name;

  for (unsigned int i = 0; i < room.length(); i++) {
    if (isdigit(room[i])) {
      break;
    }
    if (room[i] == '-')
      name += ' ';
    else
      name += (room[i] - 'a' + number)%26 + 'a';
  }
  return name + " - " +std::to_string(number);
}

TEST(AdventOfCode4, Test3)
{
  ASSERT_EQ(343, getRoomNumber("qzmt-zixmtkozy-ivhz-343[z]"));
  std::cout << "[" << decryptRoom("qzmt-zixmtkozy-ivhz-343[z]") << "]";
  ASSERT_TRUE(decryptRoom("qzmt-zixmtkozy-ivhz-343[z]") == "very encrypted name  - 343");
}

TEST(AdventOfCode4, Test1)
{
  ASSERT_EQ(123, getRoomNumber("aaaaa-bbb-z-y-x-123[abxyz]"));
}

TEST(AdventOfCode4, Test2)
{
  ASSERT_EQ(0, getRoomNumber("totally-real-room-200[decoy]"));
}


TEST(AdventOfCode4, Quest1)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input4_1.txt");
  std::string str;
  int sum = 0;

  while (std::getline(file, str))
  {
//    std::cout << "Hej " << str << std::endl;
    sum += getRoomNumber(str);
  }
  std::cout << "Sum " << sum << std::endl;
}


TEST(AdventOfCode4, Quest2)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input4_1.txt");
  std::string str;
  int sum = 0;

  while (std::getline(file, str))
  {
    std::string name = decryptRoom(str);
    if(name.find("north") != std::string::npos)
      std::cout << "Room " << name.c_str() << std::endl;
  }
}


