#include "gtest\gtest.h"
#include <fstream>
class Keypad {
public:

  enum KeypadVersion {
    KEYPAD1,
    KEYPAD2
  };
  Keypad(KeypadVersion keypadVersion) : m_x(1), m_y(3) {
    if (keypadVersion == KEYPAD1) {
      m_keypad = keypadStr1;
      m_x = 2;
      m_y = 2;
    }
    if (keypadVersion == KEYPAD2) {
      m_keypad = keypadStr2;
    }
  }

  char getDigit(const std::string &sequence) {
    for (unsigned int i = 0; i < sequence.length(); i++) {
      switch (sequence[i]) {
      case 'R':
        if (m_keypad[m_y][m_x + 1] != 'X')
          m_x++;
        break;
      case 'L':
        if (m_keypad[m_y][m_x - 1] != 'X')
          m_x--;
        break;
      case 'U':
        if (m_keypad[m_y - 1][m_x] != 'X')
          m_y--;
        break;
      case 'D':
        if (m_keypad[m_y + 1][m_x] != 'X')
          m_y++;
        break;
      }
    }
    return m_keypad[m_y][m_x];
  }

  const char **m_keypad;
  static const char *keypadStr2[];
  static const char *keypadStr1[];

  int m_x;
  int m_y;
};

const char *Keypad::keypadStr1[] = {
  "XXXXX ",
  "X123X ",
  "X456X",
  "X789X",
  "XXXXX ",
};

const char *Keypad::keypadStr2[] = {
  "XXXXXXX ",
  "XXX1XXX ",
  "XX234XX",
  "X56789X",
  "XXABCXX",
  "XXXDXXX",
  "XXXXXXX ",
};


TEST(AdventOfCode2, InitialTest)
{
  Keypad keypad(Keypad::KEYPAD1);
  ASSERT_EQ(keypad.getDigit("ULL"), '1');
  ASSERT_EQ(keypad.getDigit("RRDDD"), '9');
  ASSERT_EQ(keypad.getDigit("LURDL"), '8');
  ASSERT_EQ(keypad.getDigit("UUUUD"), '5');
}

TEST(AdventOfCode2, GoLeft)
{
  Keypad keypad(Keypad::KEYPAD1);

  ASSERT_EQ(keypad.getDigit("LLLLL"), '4');
}

TEST(AdventOfCode2, GoRight)
{
  Keypad keypad(Keypad::KEYPAD1);

  ASSERT_EQ(keypad.getDigit("RRRRR"), '6');
}
TEST(AdventOfCode2, Quest1)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input2_1.txt");
  std::string str = "";

  std::string result = "";

  Keypad keypad(Keypad::KEYPAD1);

  while (std::getline(file, str)) {
    result += keypad.getDigit(str);
  }
  std::cout << "AdventOfCode2_1 " << result << std::endl;
  ASSERT_TRUE(result == "82958");
}



TEST(AdventOfCode2, Test1) {
  Keypad keypad(Keypad::KEYPAD2);

  ASSERT_EQ(keypad.getDigit("LLLLL"), '5');
}


TEST(AdventOfCode2, Test2) {
  Keypad keypad(Keypad::KEYPAD2);

  ASSERT_EQ(keypad.getDigit("RRRRRRRRRRR"), '9');
}

TEST(AdventOfCode2, Quest2)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input2_1.txt");
  std::string str = "";
  std::string result = "";
  Keypad keypad(Keypad::KEYPAD2);

  while (std::getline(file, str)) {
    result += keypad.getDigit(str);
  }
  std::cout << "AdventOfCode2_2 " << result << std::endl;
  ASSERT_TRUE(result == "B3DB8");
}
