#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day17 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day17() { }

  ~Day17() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "17\\input.txt");
  }

  string Part1() override
  {
    int ret = 171;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 172;
    return std::to_string(ret);
  }
};
