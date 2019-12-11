#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day15 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day15() { }

  ~Day15() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "15\\input.txt");
  }

  string Part1() override
  {
    int ret = 151;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 152;
    return std::to_string(ret);
  }
};
