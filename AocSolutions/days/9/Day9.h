#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day9 : public ISolutionDay
{
public:

  Day9() { }

  ~Day9() override { }

  bool mOutputPauses{ false };

  string Part1() override
  {
    IntComputer cpu(rff(KINPUT "9\\input.txt")[0]);
    cpu.mInput = 1;
    return std::to_string(cpu.Execute());
  }

  string Part2() override
  {
    IntComputer cpu(rff(KINPUT "9\\input.txt")[0]);
    cpu.mInput = 2;
    return std::to_string(cpu.Execute());
  }
};
