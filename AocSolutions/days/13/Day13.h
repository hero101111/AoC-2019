#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day13 : public ISolutionDay
{
private:

  string instr;

public:

  Day13() { }

  ~Day13() override { }

  void ReadData()
  {
    instr = rff(KINPUT "13\\input.txt")[0];
  }

  string Part1() override
  {
    ReadData();
    IntComputer cpu(instr);
    cpu.mInput = 0;

    int counter = 0;
    int blockCounter = 0;
    cpu.mOutputCallback = [&](int value) 
    {
      counter++;
      if (counter % 3 == 0)
      {
        if (value == 2)
          blockCounter++;
      }
    };
    cpu.Execute();
    int ret = blockCounter;
    return std::to_string(ret);
  }

  string Part2() override
  {
    ReadData();
    IntComputer cpu(instr);
    cpu.mInput = 0;
    cpu.SetMemoryAt(0, 2);
    
    Point ball{ -1, -1 };
    Point paddle{ -1, -1 };

    cpu.mInputFunction = [&]()
    { 
      int joyStick = 0;
      if (ball.x < paddle.x)
        joyStick = -1;
      if (ball.x > paddle.x)
        joyStick = 1;

      return joyStick; 
    };

    int counter = 0;
    int x = 0, y = 0;
    int lastScore = 0;
    cpu.mOutputCallback = [&](int value)
    {
      counter++;
      switch (counter % 3)
      {
      case 1:
        x = value;
        break;

      case 2:
        y = value;
        break;

      case 0:

        if (x == -1 && y == 0)
        {
          lastScore = value;
        }
        else
        {
          if (value == 3)
            paddle = { x, y };
          if (value == 4)
            ball = { x, y };
        }
        break;
      }
    };

    cpu.Execute();
    
    return std::to_string(lastScore);
  }
};
