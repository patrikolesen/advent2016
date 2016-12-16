#include "gtest\gtest.h"
#include <fstream>
#include <stdio.h>

/* We do assue correct input */
class Display {
public:
#if 1
  static const int width = 50;
  static const int height = 6;
#else
  static const int width = 7;
  static const int height = 3;
#endif

  Display() {
    memset(m_display, ' ', sizeof(m_display));
  };
  virtual ~Display() {};

  void rect(std::string params) {
    int x = 0;
    int y = 0;
    sscanf_s(params.c_str(), "rect %dx%d", &x, &y);
    rect(x, y);
  }

  void rotateRow(std::string params) {
    int count = 0;
    int y = 0;
    sscanf_s(params.c_str(), "rotate row y=%d by %d", &y, &count);
    rotateRow(y, count);
  }

  void rotateColumn(std::string params) {
    int count = 0;
    int x = 0;
    sscanf_s(params.c_str(), "rotate column x=%d by %d", &x, &count);
    rotateColumn(x, count);
  }

  void rect(int x, int y)
  {
    for (int i = 0; i < y; i++) {
      for (int j= 0; j < x; j++) {
        m_display[i][j] = 'X';
      }
    }
  }

  void rotateRow(int y, int count) {
    char memory[width];
    for (int i = width-1; i >= 0; i--) {
      /* Swap out*/
      if (i >= width - count) {
        memory[i + count - width] = m_display[y][i];
        if (i - count < 0)
          m_display[y][i] = memory[i];
        else
          m_display[y][i] = m_display[y][i - count];
      }
      /* Swap in */
      else if (i < count)
        m_display[y][i] = memory[i];
      else
        m_display[y][i] = m_display[y][i - count];
    }
  }

  void rotateColumn(int x, int count) {
    char memory[height];
    for (int i = height - 1; i >= 0; i--) {
      /* Swap out*/
      if (i >= height - count) {
        memory[i + count - height] = m_display[i][x];
        if (i - count < 0)
          m_display[i][x] = memory[i];
        else
          m_display[i][x] = m_display[i - count][x];
      }
      /* Swap in */
      else if (i < count)
        m_display[i][x] = memory[i];
      else
        m_display[i][x] = m_display[i - count][x];
    }
  }

  void decode(const std::string& str) {

    if (str.find("rect ") != std::string::npos) {
      rect(str);
    }
    else if (str.find("row") != std::string::npos) {
      rotateRow(str);
    }
    else if (str.find("column") != std::string::npos) {
      rotateColumn(str);
    }
  }

  char m_display[height][width];
};

TEST(AdventOfCode8, TestRotateRow) {
  Display display;
  for (int i = 0; i < Display::width; i++) {
    display.m_display[0][i] = i % 10 + '0';
  }
  display.rotateRow(0, 5);
  ASSERT_TRUE(memcmp(display.m_display[0], "56789", strlen("56789")) == 0);
}

TEST(AdventOfCode8, TestRotateColumn) {
  Display display;
  for (int i = 0; i < Display::height; i++) {
    display.m_display[i][3] = i % 10 + '0';
  }
  display.rotateColumn(3, 2);
}

#if 0
TEST(AdventOfCode8, Test) {
  Display display;
  display.decode("rect 3x2");
  display.decode("rotate column x=1 by 1");
  display.decode("rotate row y=0 by 4");
  display.decode("rotate column x=1 by 1");
}
#endif
#if 1
TEST(AdventOfCode8, Quest1) {
  std::ifstream file("C:\\programming\\adventofcode\\input\\input8.txt");
  std::string str;
  Display display;

  while (std::getline(file, str)) {
    display.decode(str);
  }
  int count = 0;

  std::cout << std::endl;
  std::cout << std::endl;
  for (int y = 0; y < Display::height; y++) {
    for (int x = 0; x < Display::width; x++) {
      std::cout << display.m_display[y][x];
      if (display.m_display[y][x] == 'X') {
        count++;
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "AdventOfCode8_1 count " << count << std::endl;
}
#endif