#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day13 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day13() { }

  ~Day13() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "13\\input.txt");
  }

  string Part1() override
  {
    int ret = 131;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 132;
    return std::to_string(ret);
  }
};
