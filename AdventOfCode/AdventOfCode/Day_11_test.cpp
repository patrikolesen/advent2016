#include <gtest\gtest.h>
#include <map>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <functional>

enum Item {
  None,
  ThuliumGenerator,
  ThuliumMicrochip,
  PlutoniumGenerator,
  PlutoniumMicrochip,
  StroniumGenerator,
  StroniumMicrochip,
  PromethiumGenerator,
  PromethiumMicrochip,
  RutheniumGenerator,
  RutheniumMicrochip,
  EleriumGenerator,
  EleriumMicrochip,
  DilithiumGenerator,
  DilithiumMicrochip
};

enum Floor {
  Floor1,
  Floor2,
  Floor3,
  Floor4,
  Elevator
};


struct Facility
{
  typedef std::map<int, std::set<int>> Location;

  bool isMicrochip(int item) const {
    return (item % 2 == 0);
  }

  bool isAllowed(std::set<int> &items) const {
    for (auto &item : items) {
      /* Is microchip? */
      if (isMicrochip(item))
      {
        /* Does my generator exist =*/
        if (items.find(item - 1) != items.end()) {
          return true;
        }
        for (auto &other : items) {
          /* Do we have any other generator? */
          if (!isMicrochip(other))
            return false;
        }
      }
    }
    return true;
  }

  void moveItems(Location &items, int item1, int item2, int from, int to) const {
    items[from].erase(item1);
    if (item1 != item2) {
      items[from].erase(item2);
      items[to].emplace(item2);
    }
    items[to].emplace(item1);
    items[Elevator] = { to };

  }

  std::vector<Location> neighbors(Location id) const {
    std::vector<Location> results;
    int elevatorFloor;
    for (auto &it : id[Elevator]) {
      elevatorFloor = it;
    }

      for (auto &item1 : id[elevatorFloor]) {
        for (auto &item2 : id[elevatorFloor]) {
          if (item2 < item1) {
            continue;
          }
          if (elevatorFloor < Floor4)
          {
            Location dest = id;
            moveItems(dest, item1, item2, elevatorFloor, elevatorFloor + 1);
            if (isAllowed(dest[elevatorFloor]) && isAllowed(dest[elevatorFloor + 1]))
              results.push_back(dest);
          }
          if (elevatorFloor > Floor1)
          {
            Location dest = id;
            moveItems(dest, item1, item2, elevatorFloor, elevatorFloor - 1);
            if (isAllowed(dest[elevatorFloor]) && isAllowed(dest[elevatorFloor - 1]) )
              results.push_back(dest);
          }
        }
      }

    return results;
  }

  double cost(Location from, Location to) const {
    return 1;
  }

  double heuristic(Location from, Location goal) const {
    int count = 0;
    for (int i = Floor1; i < Floor4; i++) {
      count += (Floor4 - i) * from[i].size() * 10000;
    }
    return count;
  }

};


template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
    std::greater<PQElement >> elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  inline T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};
template<typename Graph>
void a_star_search
(const Graph& graph,
  typename Graph::Location start,
  typename Graph::Location goal,
  std::map<typename Graph::Location, typename Graph::Location>& came_from,
  std::map<typename Graph::Location, double>& cost_so_far)
{
  typedef typename Graph::Location Location;
  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  int count = 0;
  while (!frontier.empty()) {
    auto current = frontier.get();

    if ((count++ % 100) == 0)
      std::cout << "Count " << count << " Cost " << cost_so_far[current] << " Heuristic " << graph.heuristic(current, goal) << " came_from " << came_from.size() << " fronier " << frontier.elements.size() << std::endl;
    if (current == goal) {
      break;
    }

    for (auto next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + graph.heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
}

#if 0
TEST(AdventOfCode11, astar) {
  Facility facility;
  Facility::Location start;
  Facility::Location goal;
  std::map<Facility::Location, Facility::Location> came_from;
  std::map<Facility::Location, double> cost_so_far;

  a_star_search(facility, start, goal, came_from, cost_so_far);
}
#endif

template<typename Location>
std::vector<Location> reconstruct_path(
  Location start,
  Location goal,
  std::map<Location, Location>& came_from
  ) {
  std::vector<Location> path;
  Location current = goal;
  path.push_back(current);
  while (current != start) {
    current = came_from[current];
    path.push_back(current);
  }
  //path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

void printPath(std::vector<Facility::Location> &path) {
  int i = 0;
  std::cout << "Print path: " << std::endl;
  for (auto &location : path) {
    i++;
    std::cout << "  Node " << i << " Elevator ";
    for (auto &elevator : location[Elevator]) {
      std::cout << elevator << std::endl;
    }
    for (int i = Floor1; i <= Floor4; i++) {
      std::cout << "  Floor " << i+1 << " {";
      for (auto &item : location[i]) {
        std::cout << item << " ";
      }
      std::cout << "}" << std::endl;
    }
    std::cout << std::endl;
  }
}

TEST(AdventOfCode11, test1) {
  Facility facility;
  Facility::Location start;
  start[Floor3] = { PromethiumGenerator, PromethiumMicrochip };
  start[Floor4] = { RutheniumGenerator, RutheniumMicrochip };
  start[Elevator] = { Floor3 };
  Facility::Location goal;
  goal[Floor3] = {};
  goal[Floor4] = { PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  goal[Elevator] = { Floor4 };

  std::map<Facility::Location, Facility::Location> came_from;
  std::map<Facility::Location, double> cost_so_far;

  a_star_search(facility, start, goal, came_from, cost_so_far);
}

TEST(AdventOfCode11, test3) {
  Facility facility;
  Facility::Location start;
  start[Floor1] = { PromethiumMicrochip, RutheniumMicrochip };
  start[Floor2] = { PromethiumGenerator };
  start[Floor3] = { RutheniumGenerator };
  start[Floor4] = {  };
  start[Elevator] = { Floor1 };
  Facility::Location goal;
  goal[Floor1] = {};
  goal[Floor2] = {};
  goal[Floor3] = {};
  goal[Floor4] = { PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  goal[Elevator] = { Floor4 };

  std::map<Facility::Location, Facility::Location> came_from;
  std::map<Facility::Location, double> cost_so_far;

  a_star_search(facility, start, goal, came_from, cost_so_far);
  std::vector<Facility::Location> path = reconstruct_path(start, goal, came_from);
  printPath(path);
}

/*
The first floor contains a thulium generator, a thulium - compatible microchip, a plutonium generator, and a strontium generator.
The second floor contains a plutonium - compatible microchip and a strontium - compatible microchip.
The third floor contains a promethium generator, a promethium - compatible microchip, a ruthenium generator, and a ruthenium - compatible microchip.
The fourth floor contains nothing relevant.
*/
TEST(DISABLED_AdventOfCode11, quest1) {
  Facility facility;
  Facility::Location start;
  start[Floor1] = { ThuliumGenerator, ThuliumMicrochip, PlutoniumGenerator, StroniumGenerator };
  start[Floor2] = { PlutoniumMicrochip, StroniumMicrochip };
  start[Floor3] = { PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  start[Floor4] = {};
  start[Elevator] = { Floor1 };
  Facility::Location goal;
  goal[Floor1] = {};
  goal[Floor2] = {};
  goal[Floor3] = {};
  goal[Floor4] = { ThuliumGenerator, ThuliumMicrochip, PlutoniumGenerator, PlutoniumMicrochip, 
    StroniumGenerator, StroniumMicrochip, PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  goal[Elevator] = { Floor4 };

  std::map<Facility::Location, Facility::Location> came_from;
  std::map<Facility::Location, double> cost_so_far;

  a_star_search(facility, start, goal, came_from, cost_so_far);
  std::vector<Facility::Location> path = reconstruct_path(start, goal, came_from);
  printPath(path);
}

TEST(DISABLED_AdventOfCode11, quest2) {
  Facility facility;
  Facility::Location start;
  start[Floor1] = { ThuliumGenerator, ThuliumMicrochip, PlutoniumGenerator, StroniumGenerator, EleriumGenerator, EleriumMicrochip, DilithiumGenerator, DilithiumMicrochip };
  start[Floor2] = { PlutoniumMicrochip, StroniumMicrochip };
  start[Floor3] = { PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  start[Floor4] = {};
  start[Elevator] = { Floor1 };
  Facility::Location goal;
  goal[Floor1] = {};
  goal[Floor2] = {};
  goal[Floor3] = {};
  goal[Floor4] = { ThuliumGenerator, ThuliumMicrochip, PlutoniumGenerator, PlutoniumMicrochip,
    StroniumGenerator, StroniumMicrochip, PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip, EleriumGenerator, EleriumMicrochip, DilithiumGenerator, DilithiumMicrochip };
  goal[Elevator] = { Floor4 };

  std::map<Facility::Location, Facility::Location> came_from;
  std::map<Facility::Location, double> cost_so_far;

  a_star_search(facility, start, goal, came_from, cost_so_far);
  std::vector<Facility::Location> path = reconstruct_path(start, goal, came_from);
  printPath(path);
}

#if 0
TEST(AdventOfCode11, Quest1) {
  std::map<Floor, std::vector<Item>> items;

  items[Floor1] = { ThuliumGenerator, ThuliumMicrochip, PlutoniumGenerator, StroniumGenerator };
  items[Floor2] = { PlutoniumMicrochip, StroniumMicrochip };
  items[Floor3] = { PromethiumGenerator, PromethiumMicrochip, RutheniumGenerator, RutheniumMicrochip };
  ASSERT_EQ(3, Search().search(new House(items)));
}
#endif