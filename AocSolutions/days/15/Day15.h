#pragma once

#include "SolutionDay.h"

class Day15 : public ISolutionDay
{
public:
  
  DynamicMap<char> m;
  Point oxyLocation;

  ~Day15() override { }

  Point Advance(Point p, int mode)
  {
    switch (mode)
    {
    case 1:
      return p.Up();
      break;
    case 2:
      return p.Down();
      break;
    case 3:
      return p.Left();
      break;
    case 4:
      return p.Right();
      break;
    }
  }
  vector<Point> GetNeigh(Point p, const map<Point, int> & visited)
  {
    vector<Point> pts { p.Left(), p.Right(), p.Up(), p.Down() };
    vector<Point> ret;
    for (auto p : pts)
      if (visited.find(p) == end(visited))
        ret.push_back(p);
    return ret;
  }
  int GetMode(Point from, Point to)
  {
    if (to.y < from.y) return 1;
    if (to.y > from.y) return 2;
    if (to.x < from.x) return 3;
    if (to.x > from.x) return 4;
    assert(!"Invalid"); return 1;
  }

  int ScanMap()
  {
    IntComputer cpu{ rff(KINPUT "15\\input.txt")[0] };

    int nodeCount = 0;
    Point location;
    map<Point, int> visited;

    vector<pair<Point, int>> q;
    int crtCommand = 1;

    auto decideNextMove = [&](bool isWall)
    {
      vector<Point> neigh = GetNeigh(location, visited);

      if (isWall && !q.empty())
      {
        q.pop_back();
      }

      if (neigh.empty())
      {
        if (q.empty())
        {
          cpu.mSuspendOnOutput = true;
          return;
        }
        auto prev = q.back();
        q.pop_back();
        crtCommand = GetMode(location, prev.first);
        return;
      }

      auto next = neigh.front();
      int mode = GetMode(location, next);
      q.push_back(make_pair(location, mode));
      crtCommand = mode;
    };

    cpu.mInputFunction = [&]()
    {
      return crtCommand;
    };

    cpu.mOutputCallback = [&](int output)
    {
      switch (output)
      {
      case 0:
      {
        Point wall = Advance(location, crtCommand);
        visited[wall] = 1;
        m[wall] = '#';

        decideNextMove(true);
        break;
      }
      case 1:
      {
        visited[location] = 1;
        location = Advance(location, crtCommand);

        visited[location] = 1;
        m[location] = '.';
        ++nodeCount;

        decideNextMove(false);
        break;
      }
      case 2:
        visited[location] = 1;
        location = Advance(location, crtCommand);
        m[location] = 'O';
        ++nodeCount;
        oxyLocation = location;

        decideNextMove(false);

        break;
      }

    };

    q.push_back(make_pair(location, 1));
    cpu.Execute();
    return nodeCount;
  }

  string Part1() override
  {
    int nodeCount = ScanMap();
    Graph g(nodeCount);
    objmap<Point> mapper;

    auto isValidNode = [](char c) { return (c == 'O' || c == '.'); };
    for (int x : m.range_x())
    {
      for (int y : m.range_y())
      {
        Point p{ x, y };
        char c = m[p];

        if (isValidNode(c))
        {
          int pNode = mapper[p];
          Point pRight = p.Right();
          char r = m[pRight];
          if (isValidNode(r))
          {
            int rNode = mapper[pRight];
            g.AddEdgeSymmetrical(pNode, rNode, 1);
          }
          Point pDown = p.Down();
          char d = m[pDown];
          if (isValidNode(d))
          {
            int dNode = mapper[pDown];
            g.AddEdgeSymmetrical(pNode, dNode, 1);
          }
        }
      }
    }
    int startNode = mapper[{0, 0}];
    int oxyNode = mapper[oxyLocation];
    auto path = g.GetShortestPath(startNode, oxyNode);
    return std::to_string(path.size() - 1);
  }

  string Part2() override
  {
    int nodeCount = ScanMap();
    int minuteCount = 0;

    auto getNeighOxy = [&](Point p)
    {
      vector<Point> neigh = { p.Left(), p.Right(), p.Down(), p.Up() };
      vector<Point> ret;
      for (auto n : neigh)
        if (m.hasAt(n, '.'))
          ret.push_back(n);
      return ret;
    };

    vector<Point> oxygen;
    oxygen.push_back(oxyLocation);

    while (!oxygen.empty())
    {
      vector<Point> newOxygen;
      for (auto o : oxygen)
      {
        auto newO = getNeighOxy(o);
        copy(begin(newO), end(newO), back_inserter(newOxygen));
      }
      for (auto o : newOxygen)
        m[o] = 'O';
      oxygen = newOxygen;
      minuteCount++;
    }
    return std::to_string(minuteCount - 1);
  }
};
