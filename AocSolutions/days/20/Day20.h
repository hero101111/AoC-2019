#pragma once

#include "SolutionDay.h"

class Day20 : public ISolutionDay
{
private:

  int layers{ 30 };
  DynamicMap<char>            m;
  objmap<Point>               mapper;
  unique_ptr<Graph>           mapGraph;
  Point                       entry, exit;
  unordered_map<string, set<Point>>   portals;
  unordered_map<string, Point>        innerPortals;
  unordered_map<string, Point>        outerPortals;

  unordered_map<Point, string> positionEntities;
  int                         nodeCount = 0;

public:

  ~Day20() override { }

  void ClosePortalAt(Graph& g, Point p)
  {
    int doorIndex = mapper[p];
    auto edgesTo = g.GetEdgesFrom(doorIndex);
    for (auto eto : edgesTo)
      g.ClearEdge(doorIndex, eto);
  }

  void ConstructMapGraph()
  {
    if (mapGraph)
      return;

    // construct a graph
    mapGraph = make_unique<Graph>(nodeCount * 100);

    for (int z : rangeint(0, layers))
    {
      // generate mapping indexes
      for (int y : m.range_y())
      {
        for (int x : m.range_x())
        {
          Point p{ x, y, z };
          if (!m.hasAt(p, '.'))
            continue;

          // add to mapping hash
          int nodeIndex = mapper(p);
          nodeIndex;

          auto right = p.Right();
          if (m.hasAt(right, '.'))
          {
            int rightIndex = mapper(right);
            mapGraph->AddEdgeSymmetrical(nodeIndex, rightIndex, 1);
          }

          auto down = p.Down();
          if (m.hasAt(down, '.'))
          {
            int downIndex = mapper(down);
            mapGraph->AddEdgeSymmetrical(nodeIndex, downIndex, 1);
          }
        }
      }
    }

    // close portals on layer 0
    for (auto& p : outerPortals)
    {
      ClosePortalAt(*mapGraph, p.second);
    }

    for (int z : rangeint(1, layers))
    {
      Point layerExit = exit;
      Point layerEntry = entry;
      layerExit.z = z;
      layerEntry.z = z;
      ClosePortalAt(*mapGraph, layerExit);
      ClosePortalAt(*mapGraph, layerEntry);

      for (auto& p : outerPortals)
      {
        string portalName = p.first;
        Point outerPortalLocation = p.second;
        outerPortalLocation.z = z;
        Point innerPortalLocation = innerPortals[portalName];
        innerPortalLocation.z = z - 1;

        int innerNode = mapper[innerPortalLocation];
        int outerNode = mapper[outerPortalLocation];

        mapGraph->AddEdgeSymmetrical(innerNode, outerNode, 1);
      }
    }
  }

  bool isUpper(char c)
  {
    return c >= 'A' && c <= 'Z';
  }

  void ReadData(string filePath)
  {
    vector<string> data = rff(filePath);

    int line = 0;
    for (auto lineStr : data)
    {
      int col = 0;
      for (char c : lineStr)
      {
        Point pos{ col, line };
        m[pos] = c;

        if (c == '.')
          nodeCount++;

        col++;
      }
      line++;
    }

    int minPortalx = 9999, minPortaly = 99999, maxPortalx = -1, maxPortaly = -1;

    auto insertPortal = [&](char c1, char c2, Point p) 
    {
      if (!isupper(c1) || !isupper(c2))
        return;

      string label;
      label.push_back(c1);
      label.push_back(c2);
      positionEntities[p] = label;

      if (label == "AA")
      {
        entry = p;
      }
      else if (label == "ZZ")
      {
        exit = p;
      }
      else
      {
        portals[label].insert(p);
        if (p.x > maxPortalx)
          maxPortalx = p.x;
        if (p.x < minPortalx)
          minPortalx = p.x;
        if (p.y > maxPortaly)
          maxPortaly = p.y;
        if (p.y < minPortaly)
          minPortaly = p.y;
      }
    };

    for (auto line : m.range_y())
    {
      for (auto col : m.range_x())
      {
        Point p{ col, line };
        if (!m.hasAt(p, '.'))
          continue;

        // label UP
        char c1, c2;
        c1 = m[p.Up().Up()];
        c2 = m[p.Up()];
        insertPortal(c1, c2, p);

        // label DOWN
        c1 = m[p.Down()];
        c2 = m[p.Down().Down()];
        insertPortal(c1, c2, p);

        // label LEFT
        c1 = m[p.Left().Left()];
        c2 = m[p.Left()];
        insertPortal(c1, c2, p);

        // label RIGHT
        c1 = m[p.Right()];
        c2 = m[p.Right().Right()];
        insertPortal(c1, c2, p);
      }
    }

    for (auto portal : portals)
    {
      for (auto p : portal.second)
      {
        if (p.y == minPortaly || p.x == minPortalx || p.y == maxPortaly || p.x == maxPortalx)
          outerPortals[portal.first] = p;
        else
          innerPortals[portal.first] = p;
      }
    }
  }

  string Part1() override
  {
    ReadData(KINPUT "20\\input.txt");
    ConstructMapGraph();

    int nodeFrom = mapper[entry];
    int nodeTo = mapper[exit];

    Graph crtG = *mapGraph;

    auto dist = crtG.GetDistances(nodeFrom);

    return std::to_string(dist[nodeTo]);
  }

  string Part2() override
  {
    ReadData(KINPUT "20\\input.txt");
    ConstructMapGraph();

    Graph crtG = *mapGraph;

    int nodeFrom = mapper[entry];

    int nodeTo = mapper[exit];
    //Point destX{ 2, 21, 1 };
    //int destXNode = mapper[destX];

    auto dist = mapper.translate(crtG.GetShortestPath(nodeFrom, nodeTo));
    ofstream fOut("c:\\aoc-2019\\path.txt");
    printvec(dist, fOut);
    fOut.close();

    return std::to_string(dist.size() - 1);
  }
};
