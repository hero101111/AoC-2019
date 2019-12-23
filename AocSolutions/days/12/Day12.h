#pragma once

#include "SolutionDay.h"
#include "util/util.h"

struct Moon
{
  Point location, velocity;

  void Move(int axis)
  {
    location[axis] += velocity[axis];
  }

  int Potential() const
  {
    return abs(location.x) + abs(location.y) + abs(location.z);
  }
  int Kinetic() const
  {
    return abs(velocity.x) + abs(velocity.y) + abs(velocity.z);
  }
  int Total() const
  {
    int p = Potential();
    int k = Kinetic();
    return p * k;
  }

  bool operator ==(const Moon& other) const
  {
    return location == other.location && velocity == other.velocity;
  }
};
class Day12 : public ISolutionDay
{
private:

  vector<Moon> moons;

public:

  Day12() { }

  ~Day12() override { }

  void ReadData()
  {
    vector<string> data = rff(KINPUT "12\\input.txt");
    for (auto& d : data)
    {
      auto tokens = RegexMatch(d, R"(<x=(-?\d+), y=(-?\d+), z=(-?\d+)>)");
      Moon moon;
      moon.location = Point(tokens[0], tokens[1], tokens[2]);
      moons.push_back(moon);
    }
  }

  void SimulateGravity(int m1, int m2, long long & v1, long long & v2)
  {
    if (m2 > m1)
    {
      v1++;
      v2--;
    }
    if (m1 > m2)
    {
      v2++;
      v1--;
    }
  }

  void SimulateStep(int axis)
  {
    for (int m1 : rangeint(0, moons.size() - 2))
    {
      Moon& moon1 = moons[m1];
      for (int m2 : rangeint( m1 + 1, moons.size() - 1))
      {
        Moon& moon2 = moons[m2];
        SimulateGravity(moon1.location[axis], moon2.location[axis], moon1.velocity[axis], moon2.velocity[axis]);
      }
    }
    for (auto& m : moons)
      m.Move(axis);
  }

  string Part1() override
  {
    ReadData();

    for (int _ : rangeint( 0, 999))
    {
      for (int axis : rangeint(0, 2))
        SimulateStep(axis);
    }

    int t = 0;
    for (auto& m : moons)
      t += m.Total();

    return std::to_string(t);
  }

  string Part2() override
  {
    ReadData();

    vector<Moon> backup = moons;

    auto findCycle = [&](int axis)
    {
      long long currentStep = 0;

      while (true)
      {
        SimulateStep(axis);

        currentStep++;

        bool stop = true;
        for (int i : rangeint(0, backup.size() - 1))
        {
          if (moons[i].location[axis] != backup[i].location[axis] || 
              moons[i].velocity[axis] != backup[i].velocity[axis] )
          {
            stop = false;
            break;
          }
        }
        if (stop)
          break;
      }
      return currentStep;
    };

    return std::to_string(lcm(lcm(findCycle(0), findCycle(1)), findCycle(2)));
  }
};
