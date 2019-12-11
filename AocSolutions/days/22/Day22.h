#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day22 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day22() { }

  ~Day22() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "22\\input.txt");
  }

  string Part1() override
  {
    int ret = 221;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 222;
    return std::to_string(ret);
  }
};
