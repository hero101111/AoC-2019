#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day11 : public ISolutionDay
{
private:

  DynamicMap<int> mapdata;

public:

  Day11() { }
  ~Day11() override { }

  string DoWork(int startcolor)
  {
    IntComputer cpu(rff(KINPUT "11\\input.txt")[0]);
    cpu.mSuspendOnOutput = true;
    char dir = 'u';
    Point crtLoc{ 0, 0 };
    int crtColor = startcolor;
    while (!cpu.IsHalted())
    {
      cpu.mInput = crtColor;
      mapdata[crtLoc] = cpu.Execute();
      dir = Point::RotateDirection(dir, cpu.Execute() == 0);
      crtLoc = crtLoc.FromDirection(dir);
      crtColor = mapdata[crtLoc];
    }
    return std::to_string(mapdata.for_each([](int&) { return true;  }));
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
