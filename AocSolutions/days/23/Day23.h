#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day23 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day23() { }

  ~Day23() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "23\\input.txt");
  }

  string Part1() override
  {
    int ret = 231;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 232;
    return std::to_string(ret);
  }
};
