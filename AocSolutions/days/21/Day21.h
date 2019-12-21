#pragma once

#include "SolutionDay.h"

class Day21 : public ISolutionDay
{
public:

  ~Day21() override { }

  string DoWork(string inputFile)
  {
    ifstream inputRobot(inputFile);
    string crtInputLine;
    getline(inputRobot, crtInputLine);

    IntComputer cpu{ rff(KINPUT "21\\input.txt")[0] };

    bool eol = false;
    cpu.mInputFunction = [&]()
    {
      if (eol)
      {
        eol = false;
        return 10;
      }

      if (crtInputLine.empty() && !inputRobot.eof())
        getline(inputRobot, crtInputLine);

      int c = crtInputLine.front();
      crtInputLine.erase(begin(crtInputLine));

      if (crtInputLine.empty())
        eol = true;
      char cc = c;
      return c;
    };

    int result = 0;
    cpu.mOutputCallback = [&](int output) {
      result = output;
    };

    cpu.Execute();

    return std::to_string(result);
  }

  string Part1() override
  {
    return DoWork(KINPUT "21\\robo_part1.txt");
  }

  string Part2() override
  {
    return DoWork(KINPUT "21\\robo_part2.txt");
  }
};
