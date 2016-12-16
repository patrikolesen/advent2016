#include "gtest\gtest.h"

#include <fstream>
#include <string>
#include <unordered_map>

namespace AdventOfCode10 {
  class Receiver {
  public:
    enum Type {
      BOT,
      CONTAINER
    };
    Receiver() : m_id(0), m_value(0) {}
    virtual ~Receiver() {};
    virtual void recieve(int value) = 0;
    void setId(int id) { m_id = id; }

    int m_id;
    int m_value;
  };

  class Container : public Receiver {
  public:
    Container()  {}
    ~Container() {}
    void recieve(int value) {
      m_value = value;
    }
  };

  class Bot : public Receiver {
  public: 
    Bot() : m_low(0), m_high(0), m_value2(0) {}
    ~Bot() {}

    void setReceivers(Receiver* low, Receiver* high) {
      m_low = low;
      m_high = high;
      if (m_value2) {
        m_low->recieve(m_value);
        m_high->recieve(m_value2);
        m_value = 0;
        m_value2 = 0;
      }
    }

    void recieve(int value) {
      if (m_value == 0) {
        m_value = value;
      }
      else
      {
        int low = (m_value > value) ? value : m_value;
        int high = (m_value < value) ? value : m_value;
        if (low == 17 && high == 61) {
          std::cout << "Bot id " << m_id << std::endl;
        }
        if (m_low == 0 || m_high == 0)
        {
          m_value = low;
          m_value2 = high;
        }
        else {
          m_low->recieve(low);
          m_high->recieve(high);
          m_value = 0;
        }
      }
    }

    Receiver *m_low;
    Receiver *m_high;
    int m_value2;
  };

  class Graph {
  public:

    void setRule(int fromId, int lowId, Receiver::Type lowType, int highId, Receiver::Type highType) {
      Receiver* low = NULL;
      Receiver* high = NULL;

      if (lowType == Receiver::BOT)
        low = &m_bots[lowId];
      else {
        low = &m_containers[lowId];
      }

      if (highType == Receiver::BOT)
        high = &m_bots[highId];
      else
        high = &m_containers[highId];

      m_bots[fromId].setId(fromId);
      low->setId(lowId);
      high->setId(highId);

      m_bots[fromId].setReceivers(low, high);
    }

    void setValue(int botId, int value) {
      m_bots[botId].setId(botId);
      m_bots[botId].recieve(value);
    }

    void addCommand(const std::string& command) {
      {
        char container[2][80];

        Receiver::Type type[2];

        int botId = 0;
        int lowId = 0;
        int highId = 0;
        int value = 0;


        if (5 == sscanf_s(command.c_str(), "bot %d gives low to %s %d and high to %s %d", &botId,
          container[0], sizeof(container[0]), &lowId,
          container[1], sizeof(container[1]), &highId)) {

          for (int i = 0; i < 2; i++)
          {
            if (std::string(container[i]) == "bot")
              type[i] = Receiver::BOT;
            else 
              type[i] = Receiver::CONTAINER;
          }
          setRule(botId, lowId, type[0], highId, type[1]);
        }
        else {
          if (2 == sscanf_s(command.c_str(), "value %d goes to bot %d", &value, &botId))
            setValue(botId, value);
        }
      }
    }

    std::unordered_map<int, Bot> m_bots;
    std::unordered_map<int, Container> m_containers;
  };
}

TEST(AdventOfCode10, Quest1) {
  std::fstream file("C:\\programming\\advent2016\\input\\input10.txt");
  std::string str;
  AdventOfCode10::Graph graph;
  int i = 1;
  while (std::getline(file, str)) {
//    std::cout << i++ << " " << str << std::endl;
    graph.addCommand(str);
//      AdventOfCode10::Graph
  }
  std::cout << "Container product " << graph.m_containers[0].m_value * graph.m_containers[1].m_value * graph.m_containers[2].m_value << std::endl;
}

