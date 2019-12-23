#pragma once

#include "SolutionDay.h"

class Day23 : public ISolutionDay
{
public:

  ~Day23() override { }

  string DoWork(bool part1)
  {
    long long emptyVal = numeric_limits<long long>::max();
    int cpuCount = 50;

    vector<IntComputer> cpu(cpuCount);

    vector<bool> booted(cpuCount, false);

    vector<queue<Point>> inputQ(cpuCount);

    vector<Point> outputs(cpuCount, { emptyVal, emptyVal, emptyVal });

    Point natData{ emptyVal, emptyVal, emptyVal };
    vector<Point> sentNat;

    int crtCPU = 0;

    for (int i : rangeint(0, cpuCount - 1))
    {
      cpu[i] = IntComputer{ rff(KINPUT "23\\input.txt")[0] };

      cpu[i].mSuspendOnOutput = true;

      cpu[i].mSuspendOnInputPredicate = [](long long input) 
      {
        return input == -1;
      };

      cpu[i].mInputFunction = [&]() 
      {
        if (!booted[crtCPU])
        {
          booted[crtCPU] = true;
          return (long long)crtCPU;
        }

        if (!inputQ[crtCPU].empty())
        {
          auto& front = inputQ[crtCPU].front();
          if (front.z == 1)
          {
            long long ret = front.x;
            front.z = 2;
            return ret;
          }
          else if (front.z == 2)
          {
            long long ret = front.y;
            inputQ[crtCPU].pop();
            return ret;
          }
        }

        return (long long)-1;
      };

      cpu[i].mOutputCallback = [&](long long output) 
      {
        auto& myOutput = outputs[crtCPU];
        if (myOutput.z == emptyVal)
          myOutput.z = output;
        else if (myOutput.x == emptyVal)
          myOutput.x = output;
        else if (myOutput.y == emptyVal)
        {
          int dest = myOutput.z;
          myOutput.y = output;
          myOutput.z = 1;
          if (dest == 255)
          {
            natData = myOutput;
            myOutput = { emptyVal, emptyVal, emptyVal };
            return;
          }
          inputQ[dest].push(myOutput);

          myOutput = { emptyVal, emptyVal, emptyVal };
        }
      };
    }

    while (true)
    {
      for (crtCPU = 0; crtCPU < cpuCount; ++crtCPU)
        cpu[crtCPU].Execute();

      if (part1 && natData.x != emptyVal)
        return to_string(natData.y);

      bool isIdle = true;
      for (int i : rangeint(0, cpuCount - 1))
        if (!inputQ[i].empty() || outputs[i] != Point {emptyVal, emptyVal, emptyVal })
          isIdle = false;

      if (isIdle && natData.x != emptyVal)
      {
        inputQ[0].push(natData);

        sentNat.push_back(natData);
        if (sentNat.size() > 1 && sentNat[sentNat.size() - 1] == sentNat[sentNat.size() - 2])
        {
          return to_string(natData.y);
        }
      }
    }

    return "invalid";
  }

  string Part1() override
  {
    return DoWork(true);
  }

  string Part2() override
  {
    return DoWork(false);
  }
};
