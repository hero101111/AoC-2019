#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day10 : public ISolutionDay
{
private:

  DynamicMap<int> mapdata;
  Point           maxLocation;

public:

  Day10() { }

  ~Day10() override { }

  void ReadData()
  {
    vector<string> lines = rff(KINPUT "10\\input.txt");
    int crtLine = 0;
    for (auto& line : lines)
    {
      int crtChar = 0;
      for (char c : line)
      {
        mapdata[{crtChar, crtLine}] = c == '#' ? 1 : 0;
        crtChar++;
      }

      crtLine++;
    }

    mapdata.printf(KOUTPUT);
  }

  void Calculate(Point p)
  {
    auto visited = mapdata;

  }

  vector<Point> GetLineOfSight(Point origin, Point target)
  {
    vector<Point> ret;
    double angle = origin.Angle(target);
    for (int x : mapdata.range_x())
    {
      for (int y : mapdata.range_y())
      {
        Point candidate = { x, y };
        if (candidate == origin || candidate == target)
          continue;

        double candAngle = origin.Angle({ x, y });
        if (candAngle == angle)
          ret.push_back(candidate);
      }
    }
    return ret;
  }

  Point GetClosestAtAngle(Point origin, double angle)
  {
    vector<Point> ret;
    for (int x : mapdata.range_x())
    {
      for (int y : mapdata.range_y())
      {
        Point candidate = { x, y };

        if (candidate == origin)
          continue;

        if (mapdata[candidate] == 0)
          continue;

        double candAngle = origin.Angle(candidate);

        if (candAngle == angle)
          ret.push_back(candidate);
      }
    }
    auto min = min_element(begin(ret), end(ret), [&origin](auto& p1, auto& p2) {return origin.ManhattanDist(p1) < origin.ManhattanDist(p2); });
    return *min;
  }

  bool IsVisible(Point origin, Point target)
  {
    bool targetGoesRight = target.x > origin.x;
    bool targetGoesDown = target.y > origin.y;

    if (mapdata[target] == 0)
      return false;

    if (target == origin)
      return false;

    auto otherTargets = GetLineOfSight(origin, target);
    for (auto& other : otherTargets)
    {
      int mapContent = mapdata[other];

      if (mapContent == 0)
        continue;

      bool between = false;
      if (targetGoesRight && !targetGoesDown)
      {
        // I
        between = other.x >= origin.x && other.y <= origin.y && other.x <= target.x && other.y >= target.y;
      }
      else if (!targetGoesRight && !targetGoesDown)
      {
        // II
        between = other.x <= origin.x && other.y <= origin.y && other.x >= target.x && other.y >= target.y;
      }
      else if (!targetGoesRight && targetGoesDown)
      {
        // III
        between = other.x <= origin.x && other.y >= origin.y && other.x >= target.x && other.y <= target.y;
      }
      else if (targetGoesRight && targetGoesDown)
      {
        // IV
        between = other.x >= origin.x && other.y >= origin.y && other.x <= target.x && other.y <= target.y;
      }
      if (between)
        return false;
    }
    return true;
  }

  int GetCount(Point p)
  {
    int count = 0;
    if (mapdata[p] == 0)
      return 0;

    for (int x : mapdata.range_x())
      for (int y : mapdata.range_y())
      {
        if (IsVisible(p, { x, y }))
          count++;
      }

    return count;
  }

  string Part1() override
  {
    ReadData();

    long long t = 101;

    int maxCount = numeric_limits<int>::min();

    for (int x : mapdata.range_x())
    {
      for (int y : mapdata.range_y())
      {
        int count = GetCount({ x, y });
        if (count > maxCount)
        {
          maxCount = count;
          maxLocation = { x, y };
        }
      }
    }

    return std::to_string(maxCount);
  }

  string Part2() override
  {
    string maxCount = Part1();

    set<double> angles;

    for (int x : mapdata.range_x())
    {
      for (int y : mapdata.range_y())
      {
        if (mapdata[{x, y}] == 0)
          continue;
        if (maxLocation == Point{x, y})
          continue;

        double angle = maxLocation.Angle({ x, y });
        angles.insert(angle);
      }
    }

    Point lastAsteroid;
    int asteroidKill = 0;
    auto it = angles.begin();
    while (true)
    {
      lastAsteroid = GetClosestAtAngle(maxLocation, *it);
      mapdata[lastAsteroid] = 0;
      asteroidKill++;

      it++;
      if (it == angles.end())
        it = angles.begin();
      if (asteroidKill == 200)
        break;
    }

    long long t = lastAsteroid.x * 100 + lastAsteroid.y;
    return std::to_string(t);
  }
};
