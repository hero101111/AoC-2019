#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day25 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day25() { }

  ~Day25() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "25\\input.txt");
  }

  string Part1() override
  {
    int ret = 251;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 252;
    return std::to_string(ret);
  }
};
