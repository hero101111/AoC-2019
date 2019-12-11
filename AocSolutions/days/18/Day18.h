#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day18 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day18() { }

  ~Day18() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "18\\input.txt");
  }

  string Part1() override
  {
    int ret = 181;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 182;
    return std::to_string(ret);
  }
};
