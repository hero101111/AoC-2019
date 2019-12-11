#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "../9/Day9.h"

class Day11 : public ISolutionDay
{
private:

  DynamicMap<int> mapdata;

public:

  Day11() { }

  ~Day11() override { }

  void ReadData()
  {
  }

  string DoWork(int startcolor)
  {
    ReadData();

    DynamicMap<int> visited;

    Day9 cpu;
    cpu.mOutputPauses = true;
    cpu.ReadData(KINPUT "11\\input.txt");

    char dir = 'u';
    bool started = false;
    Point crtLoc{ 0, 0 };

    while (!cpu.Halted())
    {
      int crtColor = mapdata[crtLoc];
      if (!started)
      {
        started = true;
        crtColor = startcolor;
      }
      int colorToPaint = cpu.DoWork(crtColor);
      mapdata[crtLoc] = colorToPaint;
      visited[crtLoc]++;

      bool rotateLeft = cpu.DoWork(crtColor) == 0;
      dir = Point::RotateDirection(dir, rotateLeft);

      Point newLocation = crtLoc.FromDirection(dir);
      crtLoc = newLocation;
    }

    const int numberOfLocations = visited.for_each([](int& val) { return val >= 1;  });

    return std::to_string(numberOfLocations);
  }

  string Part1() override
  {
    return DoWork(0);
  }

  string Part2() override
  {
    DoWork(1);

    cout << "CHECK " << KOUTPUT << " FOR THE ANSWER";
    mapdata.printf(KOUTPUT, 0);

    return std::to_string(0);
  }
};
