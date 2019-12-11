#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day11 : public ISolutionDay
{
private:

  DynamicMap<int> mapdata;
  string          instructions;

public:

  Day11() { }

  ~Day11() override { }

  void ReadData()
  {
    vector<string> fileData  = rff(KINPUT "11\\input.txt");
    instructions = fileData[0];
  }

  string DoWork(int startcolor)
  {
    ReadData();

    DynamicMap<int> visited;

    IntComputer cpu(instructions);
    cpu.mSuspendOnOutput = true;

    char dir = 'u';
    bool started = false;
    Point crtLoc{ 0, 0 };

    while (!cpu.IsHalted())
    {
      int crtColor = mapdata[crtLoc];
      if (!started)
      {
        started = true;
        crtColor = startcolor;
      }

      cpu.mInput = crtColor;
      int colorToPaint = cpu.Execute();
      mapdata[crtLoc] = colorToPaint;
      visited[crtLoc]++;

      bool rotateLeft = cpu.Execute() == 0;
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
