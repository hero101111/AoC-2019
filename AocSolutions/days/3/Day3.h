#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day3 : public ISolutionDay
{
private:

  typedef vector<pair<Point, int>> MPT;
  typedef vector<Point>            SPT;

  vector<string> mData;

  MPT firstWalk, secondWalk;

  int startX{ 0 };
  int startY{ 0 };

public:

  Day3(){ }

  ~Day3() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "3\\input.txt");
  }

  MPT Walk(string dir, Point p, SPT & steps)
  {
    char direction = dir[0];
    int quantity = stoi(dir.substr(1));

    MPT ret;

    for (int i = 0; i < quantity; ++i)
    {
      switch (direction)
      {
      case 'D':
        p = p.Down();
        break;
      case 'L':
        p = p.Left();
        break;
      case 'R':
        p = p.Right();
        break;
      case 'U':
        p = p.Up();
        break;
      }

      steps.insert(begin(steps), p);

      ret.push_back(make_pair(p, steps.size()));
    }
    return ret;
  }

  void DoWork()
  {
    vector<string> firstLine = tok(mData[0]);
    vector<string> secondLine = tok(mData[1]);

    Point p1{ startX, startY };
    SPT steps1;
    for (auto& w1 : firstLine)
    {
      auto walk = Walk(w1, p1, steps1);
      p1 = walk.back().first;
      for (auto& w : walk)
        firstWalk.push_back(w);
    }

    Point p2{ startX, startY };
    SPT steps2;
    for (auto& w2 : secondLine)
    {
      auto walk = Walk(w2, p2, steps2);
      p2 = walk.back().first;
      for (auto& w : walk)
        secondWalk.push_back(w);
    }
  }

  
  string Part1() override
  {
    ReadData();
    DoWork();

    map<int, pair<Point, int>> intersections;
    for (auto& w1 : firstWalk)
    {
      for (auto& w2 : secondWalk)
      {
        if (w1.first == w2.first)
        {
          int manhattanDist = manhattan(w1.first.x, w1.first.y, startX, startY);
          intersections[manhattanDist] = w1;
        }
      }
    }

    return std::to_string(intersections.begin()->first);
  }

  string Part2() override
  {
    ReadData();
    DoWork();

    map<int, pair<Point, int>> intersections;
    for (auto& w1 : firstWalk)
    {
      for (auto& w2 : secondWalk)
      {
        if (w1.first == w2.first)
        {
          int steps = w1.second + w2.second;
          intersections[steps] = w1;
        }
      }
    }

    return std::to_string(intersections.begin()->first);
  }
};
