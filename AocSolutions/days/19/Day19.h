#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day19 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day19() { }

  ~Day19() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "19\\input.txt");
  }

  string Part1() override
  {
    int ret = 191;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 192;
    return std::to_string(ret);
  }
};
