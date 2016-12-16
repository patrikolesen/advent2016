#include "gtest\gtest.h"
#include <fstream>

enum MarkerStatus {
  NO_MARKER,
  MARKER_LEN,
  MARKER_DUP
};

uint64_t getDecodedLen(const std::string& str, int version = 1, unsigned int start = 0, unsigned int steps = 0) {
  MarkerStatus markerStatus = NO_MARKER;
  int markLen = 0;
  uint64_t markDup = 0;
  uint64_t count = 0;

  if (steps == 0)
    steps = str.length();

  for (unsigned int i = start; i < start + steps; i++) {
    if (str[i] == '(') {
      markerStatus = MARKER_LEN;
      continue;
    }

    if (markerStatus == MARKER_LEN) {
      if (str[i] == 'x') {
        markerStatus = MARKER_DUP;
        continue;
      }
      else {
        markLen = markLen * 10 + str[i] - '0';
      }
    } else if (markerStatus == MARKER_DUP) {
      if (str[i] == ')') {
        markerStatus = NO_MARKER;
        if (version == 2){
          uint64_t value = getDecodedLen(str, 2, i + 1, markLen);
          count = count + markDup*value;
        }
        else
          count += markLen*markDup;
        i += markLen;
        markLen = 0;
        markDup = 0;
        continue;
      }
      else {
        markDup = markDup * 10 + str[i] - '0';
      }
    } else {
      count++;
    }
  }
  return count;
}

TEST(AdventOfCode9, Test1) {
  ASSERT_EQ(6, getDecodedLen("ADVENT"));
  ASSERT_EQ(7, getDecodedLen("A(1x5)BC"));
  ASSERT_EQ(9, getDecodedLen("(3x3)XYZ"));
  ASSERT_EQ(11, getDecodedLen("A(2x2)BCD(2x2)EFG"));
  ASSERT_EQ(6, getDecodedLen("(6x1)(1x3)A"));
  ASSERT_EQ(18, getDecodedLen("X(8x2)(3x3)ABCY"));
}

TEST(AdventOfCode9, Test2) {
  ASSERT_EQ(9, getDecodedLen("(3x3)XYZ", 2));
  ASSERT_EQ(strlen("XABCABCABCABCABCABCY"), getDecodedLen("X(8x2)(3x3)ABCY", 2));
  ASSERT_EQ(241920, getDecodedLen("(27x12)(20x12)(13x14)(7x10)(1x12)A", 2));
  ASSERT_EQ(445, getDecodedLen("(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN", 2));
}

TEST(AdventOfCode9, Quest1) {
  std::ifstream file("C:\\programming\\adventofcode\\input\\input9.txt");
  std::string str;

  while (std::getline(file, str)) {
    std::cout << "AdventOfCode9 len " << getDecodedLen(str) << std::endl;
  }
}

TEST(AdventOfCode9, Quest2) {
  std::ifstream file("C:\\programming\\adventofcode\\input\\input9.txt");
  std::string str;

  while (std::getline(file, str)) {
    std::cout << "AdventOfCode9 len " << getDecodedLen(str, 2) << std::endl;
  }
}
