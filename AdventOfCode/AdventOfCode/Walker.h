#ifndef WALKER_H_
#define WALKER_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

class Walker
{
  static const int NR_OF_ELEMENTS = 512;

public:
  enum Direction
  {
    North,
    East,
    South,
    West,
  };

  Walker() : m_dir(North) {
    memset(m_pos, 0, sizeof(m_pos));
    memset(m_map, 0, sizeof(m_map));
  }
  virtual ~Walker() {}

  void walk(char turn, int steps)
  {
    if (turn == 'R')
      m_dir = (Direction)((m_dir + 1) % 4);
    else
      m_dir = (Direction)(((unsigned int)m_dir - 1) % 4);

    for (int i = 0; i < steps; i++)
    {
      if (m_dir >= South)
        m_pos[m_dir % 2]--;
      else
        m_pos[m_dir % 2]++;

      if (m_map[m_pos[0] + NR_OF_ELEMENTS / 2][m_pos[1] + NR_OF_ELEMENTS / 2]) {
        printf("  Found pos (%d,%d) %d\n", m_pos[0], m_pos[1], distance());
      }
      m_map[m_pos[0] + NR_OF_ELEMENTS / 2][m_pos[1] + NR_OF_ELEMENTS / 2] = true;
    }
    printf("Fasing %d (%d,%d)\n", m_dir, m_pos[0], m_pos[1]);
  }

  int distance() const {
    return abs(m_pos[0]) + abs(m_pos[1]);
  }

  int walk(char* input)
  {
    Walker walker;
    char* token = NULL;
    char* next_token = NULL;
    char* seps = ",";
    token = strtok_s(input, seps, &next_token);

    while (token != NULL)
    {
      if (token[0] == ' ')
        token++;

      printf("[%s]\n", token);
      walker.walk(token[0], atoi(&token[1]));

      token = strtok_s(NULL, seps, &next_token);
    }
    return walker.distance();
  }

  int m_pos[2];
  bool m_map[NR_OF_ELEMENTS][NR_OF_ELEMENTS];
  Direction m_dir;
};


#endif WALKER